#pragma once
#include <stddef.h>
#include <functional>
#include <exception>
#include <vector>
#include <list>
#include <set>
#include "config.h"
#include "context.h"
#include "ts_queue.h"
#include "timer.h"
#include <string.h>
#include "fd_context.h"
#include "util.h"

namespace co
{

enum class TaskState
{
    init,
    runnable,
    io_block,       // write, writev, read, select, poll, ...
    sys_block,      // co_mutex, ...
    sleep,          // sleep, nanosleep, poll(NULL, 0, timeout)
    done,
    fatal,
};

typedef std::function<void()> TaskF;

class BlockObject;
class Processer;

// 创建协程的源码文件位置
struct SourceLocation
{
    const char* file_ = nullptr;
    int lineno_ = 0;

    void Init(const char* file, int lineno)
    {
        file_ = file, lineno_ = lineno;
    }

    friend bool operator<(SourceLocation const& lhs, SourceLocation const& rhs)
    {
        if (!lhs.file_ && !rhs.file_) return false;
        if (!lhs.file_) return false;
        if (!rhs.file_) return true;

        int cmp = strcmp(lhs.file_, rhs.file_);
        if (cmp != 0) {
            return cmp == -1 ? true : false;
        }

        return lhs.lineno_ < rhs.lineno_;
    }

    std::string to_string() const
    {
        std::string s("{file:");
        if (file_) s += file_;
        s += ", line:";
        s += std::to_string(lineno_) + "}";
        return s;
    }
};

struct Task
    : public TSQueueHook, public RefObject
{
    uint64_t id_;
    TaskState state_ = TaskState::init;
    uint64_t yield_count_ = 0;
    Processer* proc_ = NULL;
    Context ctx_;
    TaskF fn_;
    std::string debug_info_;
    SourceLocation location_;
    std::exception_ptr eptr_;           // 保存exception的指针

    // Network IO block所需的数据
    // shared_ptr不具有线程安全性, 只能在协程中和SchedulerSwitch中使用.
    IoSentryPtr io_sentry_;     

    BlockObject* block_ = nullptr;      // sys_block等待的block对象
    uint32_t block_sequence_ = 0;       // sys_block等待序号(用于做超时校验)
    CoTimerPtr block_timer_;         // sys_block带超时等待所用的timer
	MininumTimeDurationType block_timeout_{ 0 }; // sys_block超时时间
    bool is_block_timeout_ = false;     // sys_block的等待是否超时

    int sleep_ms_ = 0;                  // 睡眠时间

    explicit Task(TaskF const& fn, std::size_t stack_size,
            const char* file, int lineno);
    ~Task();

    void InitLocation(const char* file, int lineno);
    void AddIntoProcesser(Processer *proc, char* shared_stack, uint32_t shared_stack_cap);

    bool SwapIn();
    bool SwapOut();

    void SetDebugInfo(std::string const& info);
    const char* DebugInfo();

    static uint64_t s_id;
    static std::atomic<uint64_t> s_task_count;

    static uint64_t GetTaskCount();

    static LFLock s_stat_lock;
    static std::set<Task*> s_stat_set;
    static std::map<SourceLocation, uint32_t> GetStatInfo();
};

} //namespace co
