#include "TDCSetup.h"

namespace PPSTimingMB
{
  void
  TDCSetup::SetConstantValues()
  {
    SetTest(false);
    SetEnableErrorMark(true);
    SetEnableErrorBypass(false);
    SetEnableError(0x7ff); // 11 bits of '1'

    SetStrobeSelect(SS_NoStrobe);

    SetEnableGlobalTrailer(false); // FIXME not yet discussed...
    SetEnableGlobalHeader(false); // FIXME not yet discussed...

    SetReadoutSingleCycleSpeed(RSC_40Mbits_s); // FIXME don't care...
    SetSerialDelay(0x0); // FIXME maybe affected by the realistic tests
    SetReadoutSpeedSelect(RO_Fixed);
    SetTokenDelay(0x0); // FIXME maybe affected by the realistic tests

    SetEnableLocalTrailer(true); // FIXME not yet discussed...
    SetEnableLocalHeader(true); // FIXME not yet discussed...
    SetMaster(true);
    SetEnableBytewise(false);

    SetBypassInputs(false); // bit 44
    SetReadoutFIFOSize(256); // maximum
    SetMaxEventSize(-1); // no limit
    SetRejectFIFOFull(true);
    SetEnableReadoutOccupancy(false);
    SetEnableReadoutSeparator(false);
    SetEnableOverflowDetect(true);

    SetKeepToken(true);

    SetEnableRelative(true);
    SetEnableAutomaticReject(false);

    /*SetEventCountOffset(0); // FIXME needs confirmation
    SetTriggerCountOffset(0);*/

    SetEnableSetCountersOnBunchReset(false); // FIXME not yet discussed...
    SetEnableMasterResetCode(false);
    SetEnableMasterResetOnEventReset(false);
    SetEnableResetChannelBufferWhenSeparator(false); // FIXME not yet discussed...
    SetEnableSeparatorOnEventReset(false);
    SetEnableSeparatorOnBunchReset(false);
    SetEnableDirectEventReset(true);
    SetEnableDirectBunchReset(true);
    SetEnableDirectTrigger(true);

    SetLowPowerMode(true);
    SetDLLControl(0x1);

    //SetDeadTime(DT_5ns); // FIXME do we force the dead time value?
    //SetTestInvert(false);
    //SetTestMode(false);

    SetModeRCCompression(true);
    SetModeRC(true);
    SetDLLMode(DLL_320MHz);
    SetPLLControl(0x4, false, false, false);

    SetSerialClockDelay(false, 0x0);
    SetIOClockDelay(false, 0x0);
    SetCoreClockDelay(false, 0x0);
    SetDLLClockDelay(false, 0x0);
    SetSerialClockSource(Serial_pll_clock_80);

    SetIOClockSource(IO_clock_40);
    SetCoreClockSource(Core_clock_40);
    SetDLLClockSource(DLL_clock_40);

    SetRollOver(0xfff); // 4095
    SetEnableTTLSerial(true);
    SetEnableTTLControl(true);
    SetEnableTTLReset(true);
    SetEnableTTLClock(false);
    SetEnableTTLHit(false);

    SetEdgesPairing(false);
    SetTriggerMatchingMode(true);
    SetLeadingMode(true);
    SetTrailingMode(true);

    SetRCAdjustment(0, 0x7);
    SetRCAdjustment(1, 0x7);
    SetRCAdjustment(2, 0x4);
    SetRCAdjustment(3, 0x2);

    SetCoarseCountOffset(0);
    SetTriggerCountOffset(0);
    SetMatchWindow(198);
    SetSearchWindow(198);
    SetRejectCountOffset(0);
    SetTDCId(0);

    SetEnableJTAGReadout(false);

    SetSetupParity(true);
  }

  void
  TDCSetup::Dump(int verb, std::ostream& os) const
  {
    os << "====================="
       << " TDC Setup register dump "
       << "====================" << std::endl;
    if (verb>1) DumpRegister(verb, os);
    os << " Enabled errors:             ";
    for (unsigned int i=0; i<11; i++) {
      if (static_cast<bool>((GetEnableError()>>i)&0x1)) os << i << " ";
    }
    os << std::endl;
    os << " Edge resolution:            " << GetEdgeResolution() << std::endl
       << " Maximal event size:         " << GetMaxEventSize() << std::endl
       << " Reject events if FIFO full? " << GetRejectFIFOFull() << std::endl
       << " Channels offset/DLL adjustments:" << std::endl
       << "   +---------------------------------------------------------+" << std::endl;
    for (unsigned int i=0; i<TDC_NUM_CHANNELS/2; i++ ) {
      os << "   |  Ch.  " << std::setw(2) << i
         << ":   0x" << std::setfill('0')
         << std::setw(3) << std::hex << static_cast<int>(GetChannelOffset(i))
         << " / 0x"
         << std::setw(3) << static_cast<int>(GetDLLAdjustment(i)) << std::dec << std::setfill(' ')
         << "   |  Ch.  " << std::setw(2) << i+TDC_NUM_CHANNELS/2
         << ":   0x" << std::setfill('0')
         << std::setw(3) << std::hex << static_cast<int>(GetChannelOffset(i+TDC_NUM_CHANNELS/2))
         << " / 0x"
         << std::setw(3) << static_cast<int>(GetDLLAdjustment(i+TDC_NUM_CHANNELS/2)) << std::dec << std::setfill(' ')
         << " |" << std::endl;
    }
    os << "   +---------------------------------------------------------+" << std::endl
       << " Width resolution:           " << GetWidthResolution() << std::endl
       << " Dead time:                  " << GetDeadTime() << std::endl
       << " Leading/trailing mode:      " << GetLeadingMode() << " / " << GetTrailingMode() << std::endl
       << " Trigger matching mode:      " << GetTriggerMatchingMode() << std::endl
       << " Edges pairing:              " << GetEdgesPairing() << std::endl;
    os << "================================="
       << "=================================" << std::endl;
  }

  std::string
  TDCSetup::GetXML() const
  {
    std::string out;
    return out;
  }

  uint32_t
  TDCSetup::GetValue(const TDCSetupRegister& reg)
  {
    switch (reg) {
      case rTestSelect:                            return IsTest();
      case rEnableErrorMark:                       return GetEnableErrorMark();
      case rEnableErrorBypass:                     return GetEnableErrorBypass();
      case rEnableError:                           return GetEnableError();
      case rReadoutSingleCycleSpeed:               return GetReadoutSingleCycleSpeed();
      case rSerialDelay:                           return GetSerialDelay();
      case rStrobeSelect:                          return GetStrobeSelect();
      case rReadoutSpeedSelect:                    return GetReadoutSpeedSelect();
      case rTokenDelay:                            return GetTokenDelay();
      case rEnableLocalTrailer:                    return GetEnableLocalTrailer();
      case rEnableLocalHeader:                     return GetEnableLocalHeader();
      case rEnableGlobalTrailer:                   return GetEnableGlobalTrailer();
      case rEnableGlobalHeader:                    return GetEnableGlobalHeader();
      case rKeepToken:                             return GetKeepToken();
      case rMaster:                                return GetMaster();
      case rEnableBytewise:                        return GetEnableBytewise();
      case rEnableSerial:                          return GetEnableSerial();
      case rEnableJTAGReadout:                     return GetEnableJTAGReadout();
      case rTDCId:                                 return GetTDCId();
      case rSelectBypassInputs:                    return GetBypassInputs();
      case rReadoutFIFOSize:                       return GetReadoutFIFOSize();
      case rRejectCountOffset:                     return GetRejectCountOffset();
      case rSearchWindow:                          return GetSearchWindow();
      case rMatchWindow:                           return GetMatchWindow();
      case rLeadingResolution:                     return GetEdgeResolution();
      case rMaxEventSize:                          return GetMaxEventSize();
      case rRejectFIFOFull:                        return GetRejectFIFOFull();
      case rEnableReadoutOccupancy:                return GetEnableReadoutOccupancy();
      case rEnableReadoutSeparator:                return GetEnableReadoutSeparator();
      case rEnableOverflowDetect:                  return GetEnableOverflowDetect();
      case rEnableRelative:                        return GetEnableRelative();
      case rEnableAutomaticReject:                 return GetEnableAutomaticReject();
      case rEventCountOffset:                      return GetEventCountOffset();
      case rTriggerCountOffset:                    return GetTriggerCountOffset();
      case rEnableSetCountersOnBunchReset:         return GetEnableSetCountersOnBunchReset();
      case rEnableMasterResetCode:                 return GetEnableMasterResetCode();
      case rEnableMasterResetOnEventReset:         return GetEnableMasterResetOnEventReset();
      case rEnableResetChannelBufferWhenSeparator: return GetEnableResetChannelBufferWhenSeparator();
      case rEnableSeparatorOnEventReset:           return GetEnableSeparatorOnEventReset();
      case rEnableSeparatorOnBunchReset:           return GetEnableSeparatorOnBunchReset();
      case rEnableDirectEventReset:                return GetEnableDirectEventReset();
      case rEnableDirectBunchReset:                return GetEnableDirectBunchReset();
      case rEnableDirectTrigger:                   return GetEnableDirectTrigger();
      case rOffset:                                return 0; //FIXME!
      case rCoarseCountOffset:                     return GetCoarseCountOffset();
      case rDLLTapAdjust:                          return GetDLLAdjustmentWord();
      case rRCAdjust:                              return GetRCAdjustmentWord();
      case rLowPowerMode:                          return GetLowPowerMode();
      case rWidthSelect:                           return GetWidthResolution();
      case rVernierOffset:                         return GetVernierOffset();
      case rDLLControl:                            return GetDLLControl();
      case rDeadTime:                              return GetDeadTime();
      case rTestInvert:                            return GetTestInvert();
      case rTestMode:                              return GetTestMode();
      case rTrailing:                              return GetTrailingMode();
      case rLeading:                               return GetLeadingMode();
      case rModeRCCompression:                     return GetModeRCCompression();
      case rModeRC:                                return GetModeRC();
      case rDLLMode:                               return GetDLLMode();
      case rPLLControl:                            return GetPLLControlWord();
      case rSerialClockDelay:                      return GetSerialClockDelay();
      case rIOClockDelay:                          return GetIOClockDelay();
      case rCoreClockDelay:                        return GetCoreClockDelay();
      case rDLLClockDelay:                         return GetDLLClockDelay();
      case rSerialClockSource:                     return GetSerialClockSource();
      case rIOClockSource:                         return GetIOClockSource();
      case rCoreClockSource:                       return GetCoreClockSource();
      case rDLLClockSource:                        return GetDLLClockSource();
      case rRollOver:                              return GetRollOver();
      case rEnableMatching:                        return GetTriggerMatchingMode();
      case rEnablePair:                            return GetEdgesPairing();
      case rEnableTTLSerial:                       return GetEnableTTLSerial();
      case rEnableTTLControl:                      return GetEnableTTLControl();
      case rEnableTTLReset:                        return GetEnableTTLReset();
      case rEnableTTLClock:                        return GetEnableTTLClock();
      case rEnableTTLHit:                          return GetEnableTTLHit();
      case rSetupParity:                           return GetSetupParity();
      default: return 0;
    }
  }

  std::ostream&
  operator<<(std::ostream& os, const TDCSetupRegister& reg) {
    switch (reg) {
      case rTestSelect:                            os << "test_select"; break;
      case rEnableErrorMark:                       os << "enable_error_mark"; break;
      case rEnableErrorBypass:                     os << "enable_error_bypass"; break;
      case rEnableError:                           os << "enable_error"; break;
      case rReadoutSingleCycleSpeed:               os << "readout_single_cycle_speed"; break;
      case rSerialDelay:                           os << "serial_delay"; break;
      case rStrobeSelect:                          os << "strobe_select"; break;
      case rReadoutSpeedSelect:                    os << "readout_speed_select"; break;
      case rTokenDelay:                            os << "token_delay"; break;
      case rEnableLocalTrailer:                    os << "enable_local_trailer"; break;
      case rEnableLocalHeader:                     os << "enable_local_header"; break;
      case rEnableGlobalTrailer:                   os << "enable_global_trailer"; break;
      case rEnableGlobalHeader:                    os << "enable_global_header"; break;
      case rKeepToken:                             os << "keep_token"; break;
      case rMaster:                                os << "master"; break;
      case rEnableBytewise:                        os << "enable_bytewise"; break;
      case rEnableSerial:                          os << "enable_serial"; break;
      case rEnableJTAGReadout:                     os << "enable_jtag_readout"; break;
      case rTDCId:                                 os << "tdc_id"; break;
      case rSelectBypassInputs:                    os << "select_bypass_inputs"; break;
      case rReadoutFIFOSize:                       os << "readout_fifo_size"; break;
      case rRejectCountOffset:                     os << "reject_count_offset"; break;
      case rSearchWindow:                          os << "search_window"; break;
      case rMatchWindow:                           os << "match_window"; break;
      case rLeadingResolution:                     os << "leading_resolution"; break;
      case rMaxEventSize:                          os << "max_event_size"; break;
      case rRejectFIFOFull:                        os << "reject_fifo_full"; break;
      case rEnableReadoutOccupancy:                os << "enable_readout_occupancy"; break;
      case rEnableReadoutSeparator:                os << "enable_readout_separator"; break;
      case rEnableOverflowDetect:                  os << "enable_overflow_detect"; break;
      case rEnableRelative:                        os << "enable_relative"; break;
      case rEnableAutomaticReject:                 os << "enable_automatic_reject"; break;
      case rEventCountOffset:                      os << "event_count_offset"; break;
      case rTriggerCountOffset:                    os << "trigger_count_offset"; break;
      case rEnableSetCountersOnBunchReset:         os << "enable_set_counters_on_bunch_reset"; break;
      case rEnableMasterResetCode:                 os << "enable_master_reset_code"; break;
      case rEnableMasterResetOnEventReset:         os << "enable_master_reset_on_event_reset"; break;
      case rEnableResetChannelBufferWhenSeparator: os << "enable_reset_channel_buffer_when_separator"; break;
      case rEnableSeparatorOnEventReset:           os << "enable_separator_on_event_reset"; break;
      case rEnableSeparatorOnBunchReset:           os << "enable_separator_on_bunch_reset"; break;
      case rEnableDirectEventReset:                os << "enable_direct_event_reset"; break;
      case rEnableDirectBunchReset:                os << "enable_direct_bunch_reset"; break;
      case rEnableDirectTrigger:                   os << "enable_direct_trigger"; break;
      case rOffset:                                os << "channels_offset"; break;
      case rCoarseCountOffset:                     os << "coarse_count_offset"; break;
      case rDLLTapAdjust:                          os << "dll_tap_adjust"; break;
      case rRCAdjust:                              os << "rc_adjust"; break;
      case rLowPowerMode:                          os << "low_power_mode"; break;
      case rWidthSelect:                           os << "width_select"; break;
      case rVernierOffset:                         os << "vernier_offset"; break;
      case rDLLControl:                            os << "dll_control"; break;
      case rDeadTime:                              os << "dead_time"; break;
      case rTestInvert:                            os << "test_invert"; break;
      case rTestMode:                              os << "test_mode"; break;
      case rTrailing:                              os << "trailing"; break;
      case rLeading:                               os << "leading"; break;
      case rModeRCCompression:                     os << "mode_rc_compression"; break;
      case rModeRC:                                os << "mode_rc"; break;
      case rDLLMode:                               os << "dll_mode"; break;
      case rPLLControl:                            os << "pll_control"; break;
      case rSerialClockDelay:                      os << "serial_clock_delay"; break;
      case rIOClockDelay:                          os << "io_clock_delay"; break;
      case rCoreClockDelay:                        os << "core_clock_delay"; break;
      case rDLLClockDelay:                         os << "dll_clock_delay"; break;
      case rSerialClockSource:                     os << "serial_clock_source"; break;
      case rIOClockSource:                         os << "io_clock_source"; break;
      case rCoreClockSource:                       os << "core_clock_source"; break;
      case rDLLClockSource:                        os << "dll_clock_source"; break;
      case rRollOver:                              os << "roll_over"; break;
      case rEnableMatching:                        os << "enable_matching"; break;
      case rEnablePair:                            os << "enable_pair"; break;
      case rEnableTTLSerial:                       os << "enable_tll_serial"; break;
      case rEnableTTLControl:                      os << "enable_ttl_control"; break;
      case rEnableTTLReset:                        os << "enable_tll_reset"; break;
      case rEnableTTLClock:                        os << "enable_tll_clock"; break;
      case rEnableTTLHit:                          os << "enable_tll_hit"; break;
      case rSetupParity:                           os << "setup_parity"; break;
      default: break;
    }
    return os;
  }
}
