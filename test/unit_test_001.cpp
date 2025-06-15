//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2025-06-14
// PURPOSE: unit tests for the AD7390/ AD7391 DACs
//          https://github.com/RobTillaart/AD7390
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)


#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "AD7390.h"


unittest_setup()
{
}


unittest_teardown()
{
}


unittest(test_begin)
{
  fprintf(stderr, "AD7390_LIB_VERSION:\t%s\n", (char *) AD7390_LIB_VERSION);
  AD5204 pot = AD5204(10, 12, 13);  //  HW SPI by default
  pot.begin();
  assertEqual(128, pot.getValue(0));

  pot.begin(42);
  assertEqual(42, pot.getValue(0));
}


unittest(test_setValue)
{
  AD5206 pot = AD5206(10, 12, 13);  //  HW SPI by default
  pot.begin();
  assertEqual(128, pot.getValue(0));

  for (int i = 0; i < pot.pmCount(); i++)
  {
    pot.setValue(i, 35);
    assertEqual(35, pot.getValue(i));
  }

  pot.setAll(42);
  for (int i = 0; i < pot.pmCount(); i++)
  {
    assertEqual(42, pot.getValue(i));
  }

  pot.setAll();
  for (int i = 0; i < pot.pmCount(); i++)
  {
    assertEqual(128, pot.getValue(i));
  }

  assertFalse(pot.setValue(6, 10));

  AD8400 p8400 = AD8400(10, 12, 13);
  assertFalse(p8400.setValue(1, 117));
}


unittest(test_setPercentage)
{
  AD5206 pot = AD5206(10, 12, 13, 7, 6);  //  SW SPI
  pot.begin();
  assertEqualFloat(50, pot.getPercentage(0), 0.5);

  for (int i = 0; i < pot.pmCount(); i++)
  {
    pot.setPercentage(i, 35);
    assertEqualFloat(35, pot.getPercentage(i), 0.5);
  }
}


unittest_main()

//  -- END OF FILE --
