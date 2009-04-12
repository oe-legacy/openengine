#include <Testing/Testing.h>

#include <Utils/Limits.h>

#include <limits.h>
#include <float.h>

using namespace OpenEngine::Utils;

int test_main(int argc, char* argv[]) {

    OE_CHECK(minValue<char>()          == CHAR_MIN);
    OE_CHECK(maxValue<char>()          == CHAR_MAX);
    OE_CHECK(minValue<unsigned char>() == 0);
    OE_CHECK(maxValue<unsigned char>() == UCHAR_MAX);

    OE_CHECK(minValue<short>()          == SHRT_MIN);
    OE_CHECK(maxValue<short>()          == SHRT_MAX);
    OE_CHECK(minValue<unsigned short>() == 0);
    OE_CHECK(maxValue<unsigned short>() == USHRT_MAX);

    OE_CHECK(minValue<int>()          == INT_MIN);
    OE_CHECK(maxValue<int>()          == INT_MAX);
    OE_CHECK(minValue<unsigned int>() == 0);
    OE_CHECK(maxValue<unsigned int>() == UINT_MAX);

    OE_CHECK(minValue<long>()          == LONG_MIN);
    OE_CHECK(maxValue<long>()          == LONG_MAX);
    OE_CHECK(minValue<unsigned long>() == 0);
    OE_CHECK(maxValue<unsigned long>() == ULONG_MAX);

    OE_CHECK(minValue<long long>()          == LLONG_MIN);
    OE_CHECK(maxValue<long long>()          == LLONG_MAX);
    OE_CHECK(minValue<unsigned long long>() == 0);
    OE_CHECK(maxValue<unsigned long long>() == ULLONG_MAX);

    OE_CHECK(minValue<float>() == FLT_MIN);
    OE_CHECK(maxValue<float>() == FLT_MAX);

    OE_CHECK(minValue<double>() == DBL_MIN);
    OE_CHECK(maxValue<double>() == DBL_MAX);

    return 0;
}
