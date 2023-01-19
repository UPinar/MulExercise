#include <iostream>
#include <cstdint>
#include <type_traits>

template <typename T, typename U>
T resizeHexValue(T hexValue, U byteCount)
{
    switch (byteCount)
    {
    case 1:
        hexValue &= 0xFF;
        break;
    case 2:
        hexValue &= 0xFFFF;
        break;
    case 4:
        hexValue &= 0xFFFFFFFF;
        break;
    case 8:
        hexValue &= 0xFFFFFFFFFFFFFFFF;
        break;
    default:
        std::cout << "Cannot do the operation with " << byteCount << " byte Count\n";
        exit(0);
    }
    return hexValue;
}


template <typename T, typename U>
T twosCompIfNegative(T value, U bitCount)
{
    if ((value >> (bitCount - 1)) == 1)
    {
        value = ~value;
        value += 0x1;
        return value;
    }
    else
        return value;
}

template <typename P, typename F, typename S, typename R>
void multiplyOperation(P val1, P val2, F firstValByte, S secondValByte, R resultByte)
{
    int firstbitCount{ firstValByte * 8 };
    int secondbitCount{ secondValByte * 8 };

    // it is imul operation
    if (std::is_signed<P>::value == 1)
    {

        if (firstValByte == 1)
        {
            int8_t firstVal = (int8_t)val1;
            val1 = twosCompIfNegative<int8_t, int>(val1, firstbitCount);
        }
        else if (firstValByte == 2)
        {
            int16_t firstVal = (int16_t)val1;
            val1 = twosCompIfNegative<int16_t, int>(val1, firstbitCount);
        }
        else if (firstValByte == 4)
        {
            int32_t firstVal = (int32_t)val1;
            val1 = twosCompIfNegative<int32_t, int>(val1, firstbitCount);
        }

        if (secondValByte == 1)
        {
            int8_t secondVal = (int8_t)val2;
            val2 = twosCompIfNegative<int8_t, int>(val2, secondbitCount);
        }
        else if (secondValByte == 2)
        {
            int16_t secondVal = (int16_t)val2;
            val2 = twosCompIfNegative<int16_t, int>(val2, secondbitCount);
        }
        else if (secondValByte == 4)
        {
            int32_t secondVal = (int32_t)val2;
            val2 = twosCompIfNegative<int32_t, int>(val2, secondbitCount);
        }

        if (resultByte == 1)
        {
            int8_t result = val1 * val2;
            std::cout << std::hex << (int)result;
        }
        else if (resultByte == 2)
        {
            int16_t result = val1 * val2;
            std::cout << std::hex << result;
        }
        else if (resultByte == 4)
        {
            int32_t result = val1 * val2;
            std::cout << std::hex << result;
        }
        else if (resultByte == 8)
        {
            int64_t result = val1 * val2;
            std::cout << std::hex << result;
        }
    }
    // it is mul operation
    else
    {
        if (firstValByte == 1)
            uint8_t firstVal = (uint8_t)val1;
        else if (firstValByte == 2)
            uint16_t firstVal = (uint16_t)val1;
        else if (firstValByte == 4)
            uint32_t firstVal = (uint32_t)val1;

        if (secondValByte == 1)
            uint8_t secondVal = (uint8_t)val2;
        else if (secondValByte == 2)
            uint16_t secondVal = (uint16_t)val2;
        else if (secondValByte == 4)
            uint32_t secondVal = (uint32_t)val2;


        if (resultByte == 1)
        {
            uint8_t result = val1 * val2;
            std::cout << std::hex << result;
        }
        else if (resultByte == 2)
        {
            uint16_t result = val1 * val2;
            std::cout << std::hex << result;
        }
        else if (resultByte == 4)
        {
            uint32_t result = val1 * val2;
            std::cout << std::hex << result;
        }
        else if (resultByte == 8)
        {
            uint64_t result = val1 * val2;
            std::cout << std::hex << result;
        }
    }
}

int main()
{

    std::cout << "What is the instruction? Imul or Mul\n";
    std::cout << "Type [i/m]\n";
    char intOrUint{};
    std::cin >> intOrUint;

    if (std::tolower(intOrUint) == 'i')
    {

        std::cout << "Enter your first hex value\n";
        uint64_t firstINT{ };
        std::cin >> std::hex >> firstINT;

        std::cout << "Size of the value will used in multiplication (bytes)\n";
        int firstvaluesByteCount{};
        std::cin >> firstvaluesByteCount;

        std::cout << "Enter your second hex value\n";
        uint64_t secondINT{};
        std::cin >> std::hex >> secondINT;

        std::cout << "Size of the value will used in multiplication (bytes)\n";
        int secondvaluesByteCount{};
        std::cin >> secondvaluesByteCount;

        std::cout << "Size of the result value (bytes)\n";
        int resultByteCount{};
        std::cin >> resultByteCount;


        int64_t firstSINT = (int64_t)(firstINT);
        int64_t secondSINT = (int64_t)(secondINT);
        firstINT = resizeHexValue<int64_t, int>(firstSINT, firstvaluesByteCount);
        secondINT = resizeHexValue<int64_t, int>(secondSINT, secondvaluesByteCount);

        multiplyOperation<int64_t, int, int, int>(firstSINT, secondSINT, firstvaluesByteCount, secondvaluesByteCount, resultByteCount);

    }
    else if (std::tolower(intOrUint) == 'm')
    {
        std::cout << "Enter your first hex value\n";
        uint64_t firstUINT{ };
        std::cin >> std::hex >> firstUINT;

        std::cout << "Size of the value will used in multiplication (bytes)\n";
        int firstvaluesByteCount{};
        std::cin >> firstvaluesByteCount;

        std::cout << "Enter your second hex value\n";
        uint64_t secondUINT{};
        std::cin >> std::hex >> secondUINT;

        std::cout << "Size of the value will used in multiplication (bytes)\n";
        int secondvaluesByteCount{};
        std::cin >> secondvaluesByteCount;

        std::cout << "Size of the result value (bytes)\n";
        int resultByteCount{};
        std::cin >> resultByteCount;

        firstUINT = resizeHexValue<uint64_t, int>(firstUINT, firstvaluesByteCount);
        secondUINT = resizeHexValue<uint64_t, int>(secondUINT, secondvaluesByteCount);

        multiplyOperation<int64_t, int, int, int>(firstUINT, secondUINT, firstvaluesByteCount, secondvaluesByteCount, resultByteCount);
    }
}

