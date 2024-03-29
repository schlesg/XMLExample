/* myExample_subscriber.cxx

A subscription example

This file is derived from code automatically generated by the rtiddsgen 
command:

rtiddsgen -language C++03 -example <arch> myExample.idl

Example subscription of type MySturct automatically generated by 
'rtiddsgen'. To test them, follow these steps:

(1) Compile this file and the example publication.

(2) Start the subscription on the same domain used for RTI Data Distribution
Service  with the command
objs/<arch>/myExample_subscriber <domain_id> <sample_count>

(3) Start the publication on the same domain used for RTI Data Distribution
Service with the command
objs/<arch>/myExample_publisher <domain_id> <sample_count>

(4) [Optional] Specify the list of discovery initial peers and 
multicast receive addresses via an environment variable or a file 
(in the current working directory) called NDDS_DISCOVERY_PEERS. 

You can run any number of publishers and subscribers programs, and can 
add and remove them dynamically from the domain.

Example:

To run the example application on domain <domain_id>:

On UNIX systems: 

objs/<arch>/myExample_publisher <domain_id> 
objs/<arch>/myExample_subscriber <domain_id> 

On Windows systems:

objs\<arch>\myExample_publisher <domain_id>  
objs\<arch>\myExample_subscriber <domain_id>   

*/

#include <algorithm>
#include <iostream>

#include <dds/sub/ddssub.hpp>
#include <dds/core/ddscore.hpp>
// Or simply include <dds/dds.hpp> 

//GS - In order to allow loading the QOSProvider
#include <dds/core/QosProvider.hpp>
#include <dds/sub/DataReader.hpp>

#include "myExample.hpp"

class MySturctReaderListener : public dds::sub::NoOpDataReaderListener<MySturct> {
  public:

    MySturctReaderListener() : count_ (0)
    {
    }

    void on_data_available(dds::sub::DataReader<MySturct>& reader)
    {
        // Take all samples
        dds::sub::LoanedSamples<MySturct> samples = reader.take();

        for ( dds::sub::LoanedSamples<MySturct>::iterator sample_it = samples.begin();
        sample_it != samples.end(); sample_it++) {

            if (sample_it->info().valid()){
                count_++;
                std::cout << sample_it->data() << std::endl; 
            }        
        }      
    }

    int count() const
    {
        return count_;
    }

  private:
    int count_;
};

void subscriber_main(int domain_id, int sample_count)
{
	rti::domain::register_type<MySturct>("MySturct");
	auto participant = dds::core::QosProvider::Default()->create_participant_from_config("ExampleDPLib::ExampleSubDP");
	dds::sub::DataReader<MySturct> reader = rti::sub::find_datareader_by_name<dds::sub::DataReader<MySturct>>(
		participant,
		"Subscriber::ExampleTopic_DR"
		);
    MySturctReaderListener listener;
	reader->listener(&listener, dds::core::status::StatusMask::data_available());
    // Create a DomainParticipant with default Qos
    //dds::domain::DomainParticipant participant(domain_id);

    //// Create a Topic -- and automatically register the type
    //dds::topic::Topic<MySturct> topic(participant, "Example MySturct");

    //// Create a DataReader with default Qos (Subscriber created in-line)
    //dds::sub::DataReader<MySturct> reader(
    //    dds::sub::Subscriber(participant),
    //    topic,
    //    dds::core::QosProvider::Default().datareader_qos(),
    //    &listener,
    //    dds::core::status::StatusMask::data_available());

    while (listener.count() < sample_count || sample_count == 0) {
        std::cout << "MySturct subscriber sleeping for 4 sec..." << std::endl;

        rti::util::sleep(dds::core::Duration(4));
    }

    // Unset the listener to allow the reader destruction
    // (rti::core::ListenerBinder can do this automatically)
    reader.listener(NULL, dds::core::status::StatusMask::none());  
}

int main(int argc, char *argv[])
{

    int domain_id = 0;
    int sample_count = 0; // infinite loop

    if (argc >= 2) {
        domain_id = atoi(argv[1]);
    }
    if (argc >= 3) {
        sample_count = atoi(argv[2]);
    }

    // To turn on additional logging, include <rti/config/Logger.hpp> and
    // uncomment the following line:
    // rti::config::Logger::instance().verbosity(rti::config::Verbosity::STATUS_ALL);

    try {
        subscriber_main(domain_id, sample_count);
    } catch (const std::exception& ex) {
        // This will catch DDS exceptions
        std::cerr << "Exception in subscriber_main(): " << ex.what() << std::endl;
        return -1;
    }

    // RTI Connext provides a finalize_participant_factory() method
    // if you want to release memory used by the participant factory singleton.
    // Uncomment the following line to release the singleton:
    //
    // dds::domain::DomainParticipant::finalize_participant_factory();

    return 0;
}

