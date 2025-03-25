/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

namespace Timer0
{

void setUp();
void runTests();

void SetModeToCTC_SetsCorrectRegisters();
void SetCompareA_SetsCorrectRegisters();
void SetCompareAToHigh_ClipsValueInRegister();
void SetCompareB_SetsCorrectRegisters();
void SetCompareBToHigh_ClipsValueInRegister();
void SetTimerClock_SetsCorrectRegisterValue();
void Stop_ClearsPrescalerBitsInRegister();

} // namespace Timer0