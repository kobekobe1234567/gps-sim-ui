
#include <uhd/types/tune_request.hpp>
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/utils/safe_main.hpp>
#include <uhd/utils/thread.hpp>
#include <boost/format.hpp>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <complex>
#include <csignal>
#include <fstream>
#include <iostream>
#include "radio_thread.h"

static uhd::tx_streamer::sptr tx_stream;
static uhd::usrp::multi_usrp::sptr usrp;
bool start;

int radio_transmit(short* sample, size_t samps_count)
{
    uhd::tx_metadata_t md;
    md.start_of_burst = start;
    if(start)
        start = false;
    md.end_of_burst   = false;
    tx_stream->send(sample, samps_count, md);
    /*uhd::async_metadata_t async_md;
    tx_stream->recv_async_msg(async_md, 1);
    if ((async_md.event_code & uhd::async_metadata_t::EVENT_CODE_UNDERFLOW) ||
        (async_md.event_code & uhd::async_metadata_t::EVENT_CODE_UNDERFLOW_IN_PACKET) ||
        (async_md.event_code & uhd::async_metadata_t::EVENT_CODE_TIME_ERROR)) {
        return RadioThread::RADIO_UNDERFLOW;
    }*/
    return RadioThread::RADIO_NOERROR;
}

void radio_setgain(double gain)
{
    usrp->set_tx_gain(gain);
}

void radio_close()
{
    usrp.reset();
}

bool radio_init(double rate, double freq, double gain)
{
    // variables to be set by po
    std::string ref = "external";
    std::string wirefmt = "sc16";
    std::string args = "master_clock_rate=52e6";
    double lo_offset = 0.0;

    // create a usrp device
    std::cout << std::endl;
    std::cout << boost::format("Creating the usrp device with: %s...") % args
              << std::endl;
    usrp = uhd::usrp::multi_usrp::make(args);

    // Lock mboard clocks
    usrp->set_clock_source(ref);

    std::cout << boost::format("Using Device: %s") % usrp->get_pp_string() << std::endl;

    std::cout << boost::format("Setting TX Rate: %f Msps...") % (rate / 1e6) << std::endl;
    usrp->set_tx_rate(rate);
    std::cout << boost::format("Actual TX Rate: %f Msps...") % (usrp->get_tx_rate() / 1e6)
              << std::endl
              << std::endl;

    std::cout << boost::format("Setting TX Freq: %f MHz...") % (freq / 1e6) << std::endl;
    std::cout << boost::format("Setting TX LO Offset: %f MHz...") % (lo_offset / 1e6)
              << std::endl;
    uhd::tune_request_t tune_request;
    tune_request = uhd::tune_request_t(freq, lo_offset);
    usrp->set_tx_freq(tune_request);
    std::cout << boost::format("Actual TX Freq: %f MHz...") % (usrp->get_tx_freq() / 1e6)
              << std::endl
              << std::endl;

    // set the rf gain
        std::cout << boost::format("Setting TX Gain: %f dB...") % gain << std::endl;
        usrp->set_tx_gain(gain);
        std::cout << boost::format("Actual TX Gain: %f dB...") % usrp->get_tx_gain()
                  << std::endl
                  << std::endl;

    // allow for some setup time:
#ifdef _WIN32
    Sleep(1000);
#else
    sleep(1);
#endif

    // Check Ref and LO Lock detect
    std::vector<std::string> sensor_names;
    sensor_names = usrp->get_tx_sensor_names(0);
    if (std::find(sensor_names.begin(), sensor_names.end(), "lo_locked")
        != sensor_names.end()) {
        uhd::sensor_value_t lo_locked = usrp->get_tx_sensor("lo_locked", 0);
        std::cout << boost::format("Checking TX: %s ...") % lo_locked.to_pp_string()
                  << std::endl;
        UHD_ASSERT_THROW(lo_locked.to_bool());
    }
    sensor_names = usrp->get_mboard_sensor_names(0);
    if ((ref == "external")
        and (std::find(sensor_names.begin(), sensor_names.end(), "ref_locked")
                != sensor_names.end())) {
        uhd::sensor_value_t ref_locked = usrp->get_mboard_sensor("ref_locked", 0);
        std::cout << boost::format("Checking TX: %s ...") % ref_locked.to_pp_string()
                  << std::endl;
        if(!ref_locked.to_bool())
            return false;
    }

    // create a transmit streamer
    std::string cpu_format;
    std::vector<size_t> channel_nums;
    cpu_format = "sc16";
    uhd::stream_args_t stream_args(cpu_format, wirefmt);
    channel_nums.push_back(0);
    stream_args.channels             = channel_nums;
    tx_stream = usrp->get_tx_stream(stream_args);
    start = true;
    return true;
}
