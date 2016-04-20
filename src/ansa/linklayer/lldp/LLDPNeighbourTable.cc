//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "ansa/linklayer/lldp/LLDPNeighbourTable.h"

namespace inet {


std::string LLDPNeighbour::info() const
{
    std::stringstream string;

    string << chassisId;
    return string.str();
}


///************************ LLDP AGENT TABLE ****************************///


LLDPNeighbourTable::LLDPNeighbourTable() {
    // TODO Auto-generated constructor stub

}

LLDPNeighbour * LLDPNeighbourTable::findAgentByMSAP(const char *chassisId, const char *portId)
{
    std::vector<LLDPNeighbour *>::iterator it;

    for (it = neighbours.begin(); it != neighbours.end(); ++it)
    {// through all neighbours search for same MSAP
        //if((*it)->getInterfaceId() == ifaceId)
        //{// found same
        //    return (*it);
        //}
    }

    return nullptr;
}


LLDPNeighbour * LLDPNeighbourTable::addNeighbour(LLDPNeighbour * neighbour)
{
    /*if(findAgentByMSAP(neighbour->getChassisId(), neighbour->getPortId()) != NULL)
    {// neighbour already in table
        throw cRuntimeError("Adding to LLDPNeighbourTable neighbour, which is already in it - id %d", neighbour);
    }

    neighbours.push_back(neighbour);*/

    return neighbour;
}

/**
 * Remove neighbour
 *
 * @param   neighbour   neighbour to delete
 *
 */
void LLDPNeighbourTable::removeNeighbour(LLDPNeighbour * neighbour)
{
    std::vector<LLDPNeighbour *>::iterator it;

    for (it = neighbours.begin(); it != neighbours.end();)
    {// through all neighbours
        if((*it) == neighbour)
        {// found same
            delete (*it);
            it = neighbours.erase(it);
            return;
        }
        else
        {// do not delete -> get next
            ++it;
        }
    }
}

/**
 * Removes neighbour
 *
 * @param   chassisId   chassis ID
 * @param   portId      port ID
 */
void LLDPNeighbourTable::removeNeighbour(const char *chassisId, const char *portId)
{
    std::vector<LLDPNeighbour *>::iterator it;

    /*for (it = neighbours.begin(); it != neighbours.end();)
    {// through all neighbours
        if((*it)->getInterfaceId() == ifaceId)
        {// found same
            delete (*it);
            it = neighbours.erase(it);
            return;
        }        else
        {// do not delete -> get next
            ++it;
        }
    }*/
}

LLDPNeighbourTable::~LLDPNeighbourTable()
{
    std::vector<LLDPNeighbour *>::iterator it;

    for (it = neighbours.begin(); it != neighbours.end(); ++it)
    {// through all neighbours
        delete (*it);
    }
    neighbours.clear();
}


std::string LLDPNeighbourTable::printStats()
{
    std::stringstream string;
    std::vector<LLDPNeighbour *>::iterator it;

    //for (it = neighbours.begin(); it != neighbours.end(); ++it)
    //{// through all neighbours
        //if((*it)->getAdminStatus() != AS::disabled)
        //{
            //string << (*it)->getIfaceName() << " interface statistics:" << endl;
/*
            string << "Received " << (*it)->rxStat.str();
            if((*it)->rxStat.tlv[tlvT::UPDATE].getCount() > 0) string << "Update avg. size: " << ((*it)->rxStat.tlv[tlvT::ROUTERID].getSum() + (*it)->rxStat.tlv[tlvT::NEXTHOP].getSum() + (*it)->rxStat.tlv[tlvT::UPDATE].getSum()) / static_cast<double>((*it)->rxStat.tlv[tlvT::UPDATE].getCount()) << " B/TLV" << endl;

            string << endl << "Transmitted " << (*it)->txStat.str();
            if((*it)->txStat.tlv[tlvT::UPDATE].getCount() > 0) string << "Update avg. size: " << ((*it)->txStat.tlv[tlvT::ROUTERID].getSum() + (*it)->txStat.tlv[tlvT::NEXTHOP].getSum() + (*it)->txStat.tlv[tlvT::UPDATE].getSum()) / static_cast<double>((*it)->txStat.tlv[tlvT::UPDATE].getCount()) << " B/TLV" << endl;
            */
      //  }
    //}
    return string.str();
}
} /* namespace inet */
