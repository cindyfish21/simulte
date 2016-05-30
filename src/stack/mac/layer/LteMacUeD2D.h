//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#ifndef _LTE_LTEMACUED2D_H_
#define _LTE_LTEMACUED2D_H_

#include "LteMacUe.h"
#include "LteMacEnbD2D.h"

class LteMacUeD2D : public LteMacUe
{
  protected:

    // reference to the eNB
    LteMacEnbD2D* enb_;

    // if true, use the preconfigured TX params for transmission, else use that signaled by the eNB
    bool usePreconfiguredTxParams_;
    UserTxParams* preconfiguredTxParams_;
    UserTxParams* getPreconfiguredTxParams();  // build and return new user tx params

    virtual int numInitStages() const { return 5; }

    /**
     * Reads MAC parameters for ue and performs initialization.
     */
    virtual void initialize(int stage);

    /**
     * Main loop
     */
    virtual void handleSelfMessage();

    /**
     * macPduMake() creates MAC PDUs (one for each CID)
     * by extracting SDUs from Real Mac Buffers according
     * to the Schedule List.
     * It sends them to H-ARQ (at the moment lower layer)
     *
     * On UE it also adds a BSR control element to the MAC PDU
     * containing the size of its buffer (for that CID)
     */
    virtual void macPduMake(LteMacScheduleList* scheduleList);

    /*
     * Build a BSR to be sent to the eNB containing the size of the buffers
     * of D2D connections
     */
    LteMacPdu* makeBsr(int size);

  public:
    LteMacUeD2D();
    virtual ~LteMacUeD2D();

    virtual bool isD2DCapable()
    {
        return true;
    }

};

#endif
