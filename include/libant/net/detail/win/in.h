#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#define NO_WIN32 1
#include <winsock2.h>
#endif
#include <stdint.h>

typedef uint16_t in_port_t;
typedef uint32_t in_addr_t;
typedef int socklen_t;
typedef int ssize_t;

#ifndef NO_WIN32
typedef int sa_family_t;

#if defined(_MSC_VER)
#pragma pack(push)
#pragma pack(1)
#else
#pragma pack(1)
#endif

struct in_addr {
    in_addr_t s_addr;
};

struct sockaddr_in {
    sa_family_t sin_family;
    in_port_t sin_port;
    struct in_addr sin_addr;
    uint8_t sin_zero[8];
};

struct in6_addr {
    union {
        uint8_t __s6_addr[16];
        uint16_t __s6_addr16[8];
        uint32_t __s6_addr32[4];
    } __in6_union;
};
#define s6_addr __in6_union.__s6_addr
#define s6_addr16 __in6_union.__s6_addr16
#define s6_addr32 __in6_union.__s6_addr32

struct sockaddr_in6 {
    sa_family_t sin6_family;
    in_port_t sin6_port;
    uint32_t sin6_flowinfo;
    struct in6_addr sin6_addr;
    uint32_t sin6_scope_id;
};

struct ipv6_mreq {
    struct in6_addr ipv6mr_multiaddr;
    unsigned ipv6mr_interface;
};

#if defined(_MSC_VER)
#pragma pack(pop)
#else
#pragma pack()
#endif

#define INADDR_ANY ((in_addr_t)0x00000000)
#define INADDR_BROADCAST ((in_addr_t)0xffffffff)
#define INADDR_NONE ((in_addr_t)0xffffffff)
#define INADDR_LOOPBACK ((in_addr_t)0x7f000001)

#define IN6ADDR_ANY_INIT                                       \
    {                                                          \
        {                                                      \
            {                                                  \
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 \
            }                                                  \
        }                                                      \
    }
#define IN6ADDR_LOOPBACK_INIT                                  \
    {                                                          \
        {                                                      \
            {                                                  \
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 \
            }                                                  \
        }                                                      \
    }

#undef INET_ADDRSTRLEN
#undef INET6_ADDRSTRLEN
#define INET_ADDRSTRLEN 16
#define INET6_ADDRSTRLEN 46

#define IPPORT_RESERVED 1024

#endif

#define INADDR_UNSPEC_GROUP ((in_addr_t)0xe0000000)
#define INADDR_ALLHOSTS_GROUP ((in_addr_t)0xe0000001)
#define INADDR_ALLRTRS_GROUP ((in_addr_t)0xe0000002)
#define INADDR_ALLSNOOPERS_GROUP ((in_addr_t)0xe000006a)
#define INADDR_MAX_LOCAL_GROUP ((in_addr_t)0xe00000ff)

#ifndef NO_WIN32
#define IPPROTO_IP 0
#define IPPROTO_HOPOPTS 0
#define IPPROTO_ICMP 1
#define IPPROTO_IGMP 2
#define IPPROTO_IPIP 4
#define IPPROTO_TCP 6
#define IPPROTO_EGP 8
#define IPPROTO_PUP 12
#define IPPROTO_UDP 17
#define IPPROTO_IDP 22
#define IPPROTO_TP 29
#define IPPROTO_DCCP 33
#define IPPROTO_IPV6 41
#define IPPROTO_ROUTING 43
#define IPPROTO_FRAGMENT 44
#define IPPROTO_RSVP 46
#define IPPROTO_GRE 47
#define IPPROTO_ESP 50
#define IPPROTO_AH 51
#define IPPROTO_ICMPV6 58
#define IPPROTO_NONE 59
#define IPPROTO_DSTOPTS 60
#define IPPROTO_MTP 92
#define IPPROTO_BEETPH 94
#define IPPROTO_ENCAP 98
#define IPPROTO_PIM 103
#define IPPROTO_COMP 108
#define IPPROTO_SCTP 132
#define IPPROTO_MH 135
#define IPPROTO_UDPLITE 136
#define IPPROTO_MPLS 137
#define IPPROTO_RAW 255
#define IPPROTO_MAX 256

#define IN6_IS_ADDR_UNSPECIFIED(a) (((uint32_t*)(a))[0] == 0 && ((uint32_t*)(a))[1] == 0 && ((uint32_t*)(a))[2] == 0 && ((uint32_t*)(a))[3] == 0)

#define IN6_IS_ADDR_LOOPBACK(a)                                                                                                                  \
    (((uint32_t*)(a))[0] == 0 && ((uint32_t*)(a))[1] == 0 && ((uint32_t*)(a))[2] == 0 && ((uint8_t*)(a))[12] == 0 && ((uint8_t*)(a))[13] == 0 && \
     ((uint8_t*)(a))[14] == 0 && ((uint8_t*)(a))[15] == 1)

#define IN6_IS_ADDR_MULTICAST(a) (((uint8_t*)(a))[0] == 0xff)

#define IN6_IS_ADDR_LINKLOCAL(a) ((((uint8_t*)(a))[0]) == 0xfe && (((uint8_t*)(a))[1] & 0xc0) == 0x80)

#define IN6_IS_ADDR_SITELOCAL(a) ((((uint8_t*)(a))[0]) == 0xfe && (((uint8_t*)(a))[1] & 0xc0) == 0xc0)

#define IN6_IS_ADDR_V4MAPPED(a)                                                                                                                   \
    (((uint32_t*)(a))[0] == 0 && ((uint32_t*)(a))[1] == 0 && ((uint8_t*)(a))[8] == 0 && ((uint8_t*)(a))[9] == 0 && ((uint8_t*)(a))[10] == 0xff && \
     ((uint8_t*)(a))[11] == 0xff)

#define IN6_IS_ADDR_V4COMPAT(a) (((uint32_t*)(a))[0] == 0 && ((uint32_t*)(a))[1] == 0 && ((uint32_t*)(a))[2] == 0 && ((uint8_t*)(a))[15] > 1)

#define IN6_IS_ADDR_MC_NODELOCAL(a) (IN6_IS_ADDR_MULTICAST(a) && ((((uint8_t*)(a))[1] & 0xf) == 0x1))

#define IN6_IS_ADDR_MC_LINKLOCAL(a) (IN6_IS_ADDR_MULTICAST(a) && ((((uint8_t*)(a))[1] & 0xf) == 0x2))

#define IN6_IS_ADDR_MC_SITELOCAL(a) (IN6_IS_ADDR_MULTICAST(a) && ((((uint8_t*)(a))[1] & 0xf) == 0x5))

#define IN6_IS_ADDR_MC_ORGLOCAL(a) (IN6_IS_ADDR_MULTICAST(a) && ((((uint8_t*)(a))[1] & 0xf) == 0x8))

#define IN6_IS_ADDR_MC_GLOBAL(a) (IN6_IS_ADDR_MULTICAST(a) && ((((uint8_t*)(a))[1] & 0xf) == 0xe))

#define __ARE_4_EQUAL(a, b) (!((0 [a] - 0 [b]) | (1 [a] - 1 [b]) | (2 [a] - 2 [b]) | (3 [a] - 3 [b])))
#define IN6_ARE_ADDR_EQUAL(a, b) __ARE_4_EQUAL((const uint32_t*)(a), (const uint32_t*)(b))

#define IN_CLASSA(a) ((((in_addr_t)(a)) & 0x80000000) == 0)
#define IN_CLASSA_NET 0xff000000
#define IN_CLASSA_NSHIFT 24
#define IN_CLASSA_HOST (0xffffffff & ~IN_CLASSA_NET)
#define IN_CLASSA_MAX 128
#define IN_CLASSB(a) ((((in_addr_t)(a)) & 0xc0000000) == 0x80000000)
#define IN_CLASSB_NET 0xffff0000
#define IN_CLASSB_NSHIFT 16
#define IN_CLASSB_HOST (0xffffffff & ~IN_CLASSB_NET)
#define IN_CLASSB_MAX 65536
#define IN_CLASSC(a) ((((in_addr_t)(a)) & 0xe0000000) == 0xc0000000)
#define IN_CLASSC_NET 0xffffff00
#define IN_CLASSC_NSHIFT 8
#define IN_CLASSC_HOST (0xffffffff & ~IN_CLASSC_NET)
#define IN_CLASSD(a) ((((in_addr_t)(a)) & 0xf0000000) == 0xe0000000)
#define IN_MULTICAST(a) IN_CLASSD(a)
#define IN_EXPERIMENTAL(a) ((((in_addr_t)(a)) & 0xe0000000) == 0xe0000000)
#define IN_BADCLASS(a) ((((in_addr_t)(a)) & 0xf0000000) == 0xf0000000)

#define IN_LOOPBACKNET 127

#define IP_TOS 1
#define IP_TTL 2
#define IP_HDRINCL 3
#define IP_OPTIONS 4
#define IP_ROUTER_ALERT 5
#define IP_RECVOPTS 6
#define IP_RETOPTS 7
#define IP_PKTINFO 8
#define IP_PKTOPTIONS 9
#define IP_PMTUDISC 10
#define IP_MTU_DISCOVER 10
#define IP_RECVERR 11
#define IP_RECVTTL 12
#define IP_RECVTOS 13
#define IP_MTU 14
#define IP_FREEBIND 15
#define IP_IPSEC_POLICY 16
#define IP_XFRM_POLICY 17
#define IP_PASSSEC 18
#define IP_TRANSPARENT 19
#define IP_ORIGDSTADDR 20
#define IP_RECVORIGDSTADDR IP_ORIGDSTADDR
#define IP_MINTTL 21
#define IP_NODEFRAG 22
#define IP_CHECKSUM 23
#define IP_BIND_ADDRESS_NO_PORT 24
#define IP_RECVFRAGSIZE 25
#define IP_MULTICAST_IF 32
#define IP_MULTICAST_TTL 33
#define IP_MULTICAST_LOOP 34
#define IP_ADD_MEMBERSHIP 35
#define IP_DROP_MEMBERSHIP 36
#define IP_UNBLOCK_SOURCE 37
#define IP_BLOCK_SOURCE 38
#define IP_ADD_SOURCE_MEMBERSHIP 39
#define IP_DROP_SOURCE_MEMBERSHIP 40
#define IP_MSFILTER 41
#define IP_MULTICAST_ALL 49
#define IP_UNICAST_IF 50

#define IP_RECVRETOPTS IP_RETOPTS

#define IP_PMTUDISC_DONT 0
#define IP_PMTUDISC_WANT 1
#define IP_PMTUDISC_DO 2
#define IP_PMTUDISC_PROBE 3
#define IP_PMTUDISC_INTERFACE 4
#define IP_PMTUDISC_OMIT 5

#define IP_DEFAULT_MULTICAST_TTL 1
#define IP_DEFAULT_MULTICAST_LOOP 1
#define IP_MAX_MEMBERSHIPS 20

#define MCAST_JOIN_GROUP 42
#define MCAST_BLOCK_SOURCE 43
#define MCAST_UNBLOCK_SOURCE 44
#define MCAST_LEAVE_GROUP 45
#define MCAST_JOIN_SOURCE_GROUP 46
#define MCAST_LEAVE_SOURCE_GROUP 47
#define MCAST_MSFILTER 48

#define MCAST_EXCLUDE 0
#define MCAST_INCLUDE 1

#if defined(_MSC_VER)
#pragma pack(push)
#pragma pack(1)
#else
#pragma pack(1)
#endif

struct ip_opts {
    struct in_addr ip_dst;
    char ip_opts[40];
};

struct ip_mreq {
    struct in_addr imr_multiaddr;
    struct in_addr imr_interface;
};

struct ip_mreqn {
    struct in_addr imr_multiaddr;
    struct in_addr imr_address;
    int imr_ifindex;
};

struct ip_mreq_source {
    struct in_addr imr_multiaddr;
    struct in_addr imr_interface;
    struct in_addr imr_sourceaddr;
};

struct ip_msfilter {
    struct in_addr imsf_multiaddr;
    struct in_addr imsf_interface;
    uint32_t imsf_fmode;
    uint32_t imsf_numsrc;
    struct in_addr imsf_slist[1];
};

#if defined(_MSC_VER)
#pragma pack(pop)
#else
#pragma pack()
#endif

#define IP_MSFILTER_SIZE(numsrc) (sizeof(struct ip_msfilter) - sizeof(struct in_addr) + (numsrc) * sizeof(struct in_addr))

#endif

#ifdef __cplusplus
}
#endif
