//
// Copyright (C) 2015 Andras Varga
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

#ifndef __INET_ONOERATECONTROL_H
#define __INET_ONOERATECONTROL_H

#include "RateControlBase.h"

namespace inet {
namespace ieee80211 {

/**
 * Implements the Onoe rate control algorithms.
 */
class INET_API OnoeRateControl : public RateControlBase, public cSimpleModule
{
    protected:
        const IIeee80211Mode *currentMode = nullptr;

        simtime_t timer = SIMTIME_ZERO;
        simtime_t interval = SIMTIME_ZERO;

        int numOfRetries = 0;
        int numOfSuccTransmissions = 0;
        int numOfGivenUpTransmissions = 0;

        double avgRetriesPerFrame = 0;
        int credit = 0;

    protected:
        virtual void handleMessage(cMessage *msg) override;
        void computeMode();
        void resetStatisticalVariables();
        void computeModeIfTimerIsExpired();
        void updateDisplayString();

    public:
        void initialize(const Ieee80211ModeSet *modeSet, const IIeee80211Mode *initialMode) override;

        virtual const IIeee80211Mode *getRate() override;
        virtual void frameTransmitted(const Ieee80211Frame *frame, const IIeee80211Mode *mode, int retryCount, bool isSuccessful, bool isGivenUp) override;
        virtual void frameReceived(const Ieee80211Frame *frame, const Ieee80211ReceptionIndication *receptionIndication) override;
};

} /* namespace ieee80211 */
} /* namespace inet */

#endif // infndef __INET_ONOERATECONTROL_H
