// This is not a standalone header
#ifndef STAT_H
#define STAT_H
#include <muduo/base/Timestamp.h>

class SudokuStat : boost::noncopyable
{
 public:
  SudokuStat(const ThreadPool& pool)
    : pool_(pool),
      lastSecond_(0),
      requests_(kSeconds),
      latencies_(kSeconds),
      totalRequests_(0),
      totalResponses_(0),
      totalSolved_(0),
      badRequests_(0),
      droppedRequests_(0),
      totalLatency_(0),
      badLatency_(0),latencies_per_request_(kSeconds)
  {
  }

  string report() const
  {
    LogStream result;
    size_t queueSize = pool_.queueSize();
    result << "1. task_queue_size " << queueSize << '\n';

    {
    MutexLockGuard lock(mutex_);
    result << "2. total_requests " << totalRequests_ << '\n';
    result << "3. total_responses " << totalResponses_ << '\n';
    result << "4. total_solved " << totalSolved_ << '\n';
    result << "5. bad_requests " << badRequests_ << '\n';
    result << "6. dropped_requests " << droppedRequests_ << '\n';
    result << "7. latency_sum_us " << totalLatency_ << '\n';
    if (badLatency_ > 0)
    {
      result << "8. bad_latency " << badLatency_ << '\n';
    }

    result << "9. last_second Timestamp " << lastSecond_ << '\n';
    result << "10. last_second " << muduo::Timestamp(lastSecond_*1000*1000).toFormattedString(false) << '\n';
    result << "11. now Timestamp " << muduo::Timestamp::now().toString() << '\n';
    result << "12. now time " << muduo::Timestamp::now().toFormattedString(false) << '\n';
    result << "13. latency_per_request_60 ";
    //过去60个请求，每个请求的延迟
    int64_t latencies_of_60=0;
    for (size_t i = 0; i < latencies_per_request_.size(); ++i)
    {
      latencies_of_60 += latencies_per_request_[i];
      result << ' ' << latencies_per_request_[i];
    }
    result << '\n';
    result << "14. latency_per_request_60_avg " << latencies_of_60/60 << '\n';


    int64_t requests = 0;
    result << "15. requests_per_second";
    for (size_t i = 0; i < requests_.size(); ++i)
    {
      requests += requests_[i];
      result << ' ' << requests_[i];
    }
    result << '\n';
    result << "16. requests_60s total " << requests << '\n';

    int64_t latency = 0;
    result << "17. latency_sum_us_per_second";
    //每秒钟的所有请求的延迟的累加
    for (size_t i = 0; i < latencies_.size(); ++i)
    {
      latency += latencies_[i];
      result << ' ' << latencies_[i];
    }
    result << '\n';
    result << "18. latency_sum_us_60s total " << latency << '\n';
    int64_t latencyAvg60s = requests == 0 ? 0 : latency / requests;
    result << "19. latency_us_60s(18/16) " << latencyAvg60s << '\n';
    int64_t latencyAvg = totalResponses_ == 0 ? 0 : totalLatency_ / totalResponses_;
    result << "20. latency_us_avg(7/3) " << latencyAvg << '\n';
    
    }

    return result.buffer().toString();
  }

  string reset()
  {
    {
    MutexLockGuard lock(mutex_);
    lastSecond_ = 0;
    requests_.clear();
    latencies_.clear();
    totalRequests_ = 0;
    totalResponses_ = 0;
    totalSolved_ = 0;
    badRequests_ = 0;
    totalLatency_ = 0;
    badLatency_ = 0;
    }
    return "reset done.";
  }

  void recordResponse(Timestamp now, Timestamp receive, bool solved)
  {
    const time_t second = now.secondsSinceEpoch();
    const int64_t elapsed_us = now.microSecondsSinceEpoch() - receive.microSecondsSinceEpoch();

    MutexLockGuard lock(mutex_);
    latencies_per_request_.push_back(elapsed_us);
    assert(requests_.size() == latencies_.size());
    ++totalResponses_;
    if (solved)
      ++totalSolved_;
    if (elapsed_us < 0)
    {
      ++badLatency_;
      return;
    }
    totalLatency_ += elapsed_us;

    const time_t firstSecond = lastSecond_ - static_cast<ssize_t>(requests_.size()) + 1;
    if (lastSecond_ == second)
    {
      // the most common case
      ++requests_.back();
      latencies_.back() += elapsed_us;
    }
    else if (lastSecond_ + 1 == second || lastSecond_ == 0)
    {
      // next second
      lastSecond_ = second;
      requests_.push_back(0);
      latencies_.push_back(0);
      ++requests_.back();
      latencies_.back() += elapsed_us;
    }
    else if (second > lastSecond_)
    {
      // jump ahead
      if (second < lastSecond_ + kSeconds)
      {
        // eg. lastSecond_ == 100, second < 160
        while (lastSecond_ < second)
        {
          requests_.push_back(0);
          latencies_.push_back(0);
          ++lastSecond_;
        }
      }
      else
      {
        // eg. lastSecond_ == 100, second >= 160
        requests_.clear();
        latencies_.clear();
        lastSecond_ = second;
        requests_.push_back(0);
        latencies_.push_back(0);
      }
      ++requests_.back();
      latencies_.back() += elapsed_us;
    }
    else if (second >= firstSecond)
    {
      // jump backwards
      // eg. lastSecond_ = 150, size = 10, second > 140
      // FIXME: if second > lastSecond_ - kSeconds, push_front()

      size_t idx = second - firstSecond;
      assert(idx < requests_.size());
      ++requests_[idx];
      latencies_[idx] += elapsed_us;
    }
    else
    {
      assert(second < firstSecond);
      // discard
      // eg. lastSecond_ = 150, size = 10, second <= 140
    }
    assert(requests_.size() == latencies_.size());
  }

  void recordRequest()
  {
    MutexLockGuard lock(mutex_);
    ++totalRequests_;
  }

  void recordBadRequest()
  {
    MutexLockGuard lock(mutex_);
    ++badRequests_;
  }

  void recordDroppedRequest()
  {
    MutexLockGuard lock(mutex_);
    ++droppedRequests_;
  }

 private:
  const ThreadPool& pool_;  // only for ThreadPool::queueSize()
  mutable MutexLock mutex_;
  // invariant:
  // 0. requests_.size() == latencies_.size()
  // 1. if lastSecond_ > 0, requests_.back() is for that second
  // 2. requests_.front() is for second (last second - size() + 1)
  time_t lastSecond_;
  boost::circular_buffer<int64_t> requests_;
  boost::circular_buffer<int64_t> latencies_;
  boost::circular_buffer<int64_t> latencies_per_request_;
  int64_t totalRequests_, totalResponses_, totalSolved_, badRequests_, droppedRequests_, totalLatency_, badLatency_;
  // FIXME int128_t for totalLatency_;

  static const int kSeconds = 60;
};

#endif