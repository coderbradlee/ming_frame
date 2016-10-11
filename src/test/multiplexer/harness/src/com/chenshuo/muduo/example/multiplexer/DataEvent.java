package com.chenshuo.muduo.example.multiplexer;

import java.nio.charset.Charset;

import io.netty.buffer.ChannelBuffer;

public class DataEvent extends Event {

    public final EventSource source;
    public final int whichClient;
    public final ChannelBuffer data;

    public DataEvent(EventSource source, int whichClient, ChannelBuffer data) {
        this.source = source;
        this.whichClient = whichClient;
        this.data = data;
    }

    public String getString() {
        return data.toString(Charset.defaultCharset());
    }
}
