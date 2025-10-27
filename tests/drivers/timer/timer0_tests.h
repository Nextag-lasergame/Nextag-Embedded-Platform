/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

namespace Timer0Tests
{

void setUp();
void runTests();

void SetModeToCTC_SetsCorrectRegisters();
void SetCompareA_SetsCorrectRegisters();
void SetCompareB_SetsCorrectRegisters();
void SetTimerClock_SetsCorrectRegisterValue();
void Stop_ClearsPrescalerBitsInRegister();

} // namespace Timer0Tests