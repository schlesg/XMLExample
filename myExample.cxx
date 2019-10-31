

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from myExample.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#include <iosfwd>
#include <iomanip>

#include "rti/topic/cdr/Serialization.hpp"

#include "myExample.hpp"
#include "myExamplePlugin.hpp"

#include <rti/util/ostream_operators.hpp>

// ---- MySturct: 

MySturct::MySturct() :
    m_x_ (0)  {
}   

MySturct::MySturct (
    int32_t x)
    :
        m_x_( x ) {
}

#ifdef RTI_CXX11_RVALUE_REFERENCES
#ifdef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
MySturct::MySturct(MySturct&& other_) OMG_NOEXCEPT  :m_x_ (std::move(other_.m_x_))
{
} 

MySturct& MySturct::operator=(MySturct&&  other_) OMG_NOEXCEPT {
    MySturct tmp(std::move(other_));
    swap(tmp); 
    return *this;
}
#endif
#endif   

void MySturct::swap(MySturct& other_)  OMG_NOEXCEPT 
{
    using std::swap;
    swap(m_x_, other_.m_x_);
}  

bool MySturct::operator == (const MySturct& other_) const {
    if (m_x_ != other_.m_x_) {
        return false;
    }
    return true;
}
bool MySturct::operator != (const MySturct& other_) const {
    return !this->operator ==(other_);
}

// --- Getters and Setters: -------------------------------------------------
int32_t& MySturct::x() OMG_NOEXCEPT {
    return m_x_;
}

const int32_t& MySturct::x() const OMG_NOEXCEPT {
    return m_x_;
}

void MySturct::x(int32_t value) {
    m_x_ = value;
}

std::ostream& operator << (std::ostream& o,const MySturct& sample)
{
    rti::util::StreamFlagSaver flag_saver (o);
    o <<"[";
    o << "x: " << sample.x() ;
    o <<"]";
    return o;
}

// --- Type traits: -------------------------------------------------

namespace rti { 
    namespace topic {

        template<>
        struct native_type_code<MySturct> {
            static DDS_TypeCode * get()
            {
                static RTIBool is_initialized = RTI_FALSE;

                static DDS_TypeCode_Member MySturct_g_tc_members[1]=
                {

                    {
                        (char *)"x",/* Member name */
                        {
                            0,/* Representation ID */          
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL/* Ignored */
                    }
                };

                static DDS_TypeCode MySturct_g_tc =
                {{
                        DDS_TK_STRUCT,/* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"MySturct", /* Name */
                        NULL, /* Ignored */      
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        1, /* Number of members */
                        MySturct_g_tc_members, /* Members */
                        DDS_VM_NONE  /* Ignored */         
                    }}; /* Type code for MySturct*/

                if (is_initialized) {
                    return &MySturct_g_tc;
                }

                MySturct_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

                is_initialized = RTI_TRUE;

                return &MySturct_g_tc;
            }
        }; // native_type_code

        const dds::core::xtypes::StructType& dynamic_type<MySturct>::get()
        {
            return static_cast<const dds::core::xtypes::StructType&>(
                rti::core::native_conversions::cast_from_native<dds::core::xtypes::DynamicType>(
                    *(native_type_code<MySturct>::get())));
        }

    }
}  

namespace dds { 
    namespace topic {
        void topic_type_support<MySturct>:: register_type(
            dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            rti::domain::register_type_plugin(
                participant,
                type_name,
                MySturctPlugin_new,
                MySturctPlugin_delete);
        }

        std::vector<char>& topic_type_support<MySturct>::to_cdr_buffer(
            std::vector<char>& buffer, const MySturct& sample)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = MySturctPlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample);
            rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = MySturctPlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample);
            rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support<MySturct>::from_cdr_buffer(MySturct& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = MySturctPlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create MySturct from cdr buffer");
        }

        void topic_type_support<MySturct>::reset_sample(MySturct& sample) 
        {
            rti::topic::reset_sample(sample.x());
        }

        void topic_type_support<MySturct>::allocate_sample(MySturct& sample, int, int) 
        {
        }

    }
}  

