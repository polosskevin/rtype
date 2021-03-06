//
// Created by Kévin POLOSSAT on 22/01/2018.
//

#include <iostream>
#include <array>
#include "Resolver.h"
#include "UDPNonBlockingCommunication.h"

void ge::network::UDPNonBlockingCommuncation::send() {
    while (!toSend_.empty()) {
        auto & s = toSend_.front();
        for (auto & ep : dest_) {
            auto e = lw_network::no_error;
            auto b = lw_network::Buffer(const_cast<char *>(s.data()), s.size());
            auto nbyte = s_.sendto(ep, b, 0, e);
            // TODO DO SOMETHING ?
        }
        toSend_.pop();
    }
}

void ge::network::UDPNonBlockingCommuncation::recv() {
	for (int i = 0; i < 10; ++i) { // TODO limit here ??
        auto e = lw_network::no_error;
        lw_network::EndPoint ep;
        auto b = lw_network::Buffer(bRead_.data(), bRead_.size());
        auto nbyte = s_.recvfrom(ep, b, 0, e);
        if (e != lw_network::no_error) {
            break;
        }
        else {
            handler_(bRead_.data(), nbyte);
        }
    }
}

void ge::network::UDPNonBlockingCommuncation::close() {
    auto e = lw_network::no_error;
    s_.close(e);
}

bool ge::network::UDPNonBlockingCommuncation::open(std::string const &port) {
    s_.openAsUdp(port);
    auto e = lw_network::no_error;
    s_.nonBlocking(true, e);
    return s_.isOpen();
}

void ge::network::UDPNonBlockingCommuncation::addHandle(ge::network::UDPNonBlockingCommuncation::Handle h) {
    handler_ = h;
}

void ge::network::UDPNonBlockingCommuncation::addDest(lw_network::EndPoint const &ep) {
    dest_.push_back(ep);
}

void ge::network::UDPNonBlockingCommuncation::addDest(std::string const &hostName, std::string const &port) {
    lw_network::Resolver re;
    re
            .SetNode(hostName)
            .SetService(port)
            .SetFamily(AF_INET)
            .SetSockType(SOCK_DGRAM);
    lw_network::EndPoint ep = re.Resolve().front();
    this->addDest(ep);
}

std::string ge::network::UDPNonBlockingCommuncation::getPort() const {
    auto e = lw_network::no_error;
    auto ep = s_.localEndPoint(e);
    return ep.PortStr();
}

void ge::network::UDPNonBlockingCommuncation::addDests(std::vector<std::pair<std::string, std::string>> const &ipAndPort) {
    for (auto const & p : ipAndPort) {
        this->addDest(p.first, p.second);
    }
}
