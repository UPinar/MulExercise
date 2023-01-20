#include <iostream>
#include <cstdint>
#include <type_traits>
#include <cstdlib>

template <typename T>
T resizeHexValue(T hexValue, int byteCount)
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


template <typename T>
T twosCompIfNegative(T value, int bitCount)
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

// class template
/*
template <typename typeOfResult, typename typeVals>
struct printResult {
    printResult(typeVals val1, typeVals val2 , int byteCount = 0)
    {
        typeOfResult result =(typeOfResult) (val1 * val2);
        if (byteCount != 1)
            std::cout << std::hex << result << '\n';
        else
            std::cout << std::hex << (int)result << '\n';
    }
};
*/


//function template
template <typename typeOfResult, typename typeVals>
void printResult(typeVals val1, typeVals val2, int byteCount = 0) {
    typeOfResult result = (typeOfResult)(val1 * val2);
    if (byteCount != 1)
        std::cout << std::hex << result << '\n';
    else
        std::cout << std::hex << (int)result << '\n';
}

template <typename T>
void multiplyOperation(T val1, T val2, int firstValByte, int secondValByte, int resultByte)
{
    int firstbitCount{ firstValByte * 8 };
    int secondbitCount{ secondValByte * 8 };


    // if the instruction is IMUL
    if (std::is_signed<T>::value == 1)
    {
        if (firstValByte == 1)
            val1 = twosCompIfNegative<int8_t>((int8_t)val1, firstbitCount);
        else if (firstValByte == 2)
            val1 = twosCompIfNegative<int16_t>((int16_t)val1, firstbitCount);
        else if (firstValByte == 4)
            val1 = twosCompIfNegative<int32_t>((int32_t)val1, firstbitCount);

        if (secondValByte == 1)
            val2 = twosCompIfNegative<int8_t>((int8_t)val2, secondbitCount);
        else if (secondValByte == 2)
            val2 = twosCompIfNegative<int16_t>((int16_t)val2, secondbitCount);
        else if (secondValByte == 4)
            val2 = twosCompIfNegative<int32_t>((int32_t)val2, secondbitCount);


        /*
        for class template
        auto result = printResult<int8_t, P>(val1, val2, resultByte);
        */

        if (resultByte == 1)
            printResult<int8_t,T>(val1, val2, resultByte);
        else if (resultByte == 2)
            printResult<int16_t, T>(val1,val2);
        else if (resultByte == 4)
            printResult<int32_t, T>(val1, val2);
        else if (resultByte == 8)
            printResult<int64_t, T>(val1, val2);
         
    }
    // if the instruction is MUL
    else
    {
        if (resultByte == 1)
            printResult<uint8_t, T>(val1, val2, resultByte);
        else if (resultByte == 2)
            printResult<uint16_t, T>(val1, val2);
        else if (resultByte == 4)
            printResult<uint32_t, T>(val1, val2);
        else if (resultByte == 8)
            printResult<uint64_t, T>(val1, val2);
    }
}

int main()
{
    char intOrUint{};
    uint64_t firstHexVal{};
    uint64_t secondHexVal{};
    int firstvaluesByteCount{};
    int secondvaluesByteCount{};
    int resultByteCount{};
    bool wantToReset{};


    while (true)
    {
        std::cout << "What is the instruction? Imul or Mul\n";
        std::cout << "Type [i/m]\n";
        std::cin >> intOrUint;

        std::cout << "Enter your first hex value\n";
        std::cin >> std::hex >> firstHexVal;

        std::cout << "Size of the value will used in multiplication (bytes)\n";
        std::cin >> firstvaluesByteCount;

        std::cout << "Enter your second hex value\n";
        std::cin >> std::hex >> secondHexVal;

        std::cout << "Size of the value will used in multiplication (bytes)\n";
        std::cin >> secondvaluesByteCount;

        std::cout << "Size of the result value (bytes)\n";
        std::cin >> resultByteCount;

        if (std::tolower(intOrUint) == 'i')
        {

            int64_t firstSignedINT = (int64_t)firstHexVal;
            int64_t secondSignedINT = (int64_t)secondHexVal;
            firstSignedINT = resizeHexValue<int64_t>(firstSignedINT, firstvaluesByteCount);
            secondSignedINT = resizeHexValue<int64_t>(secondSignedINT, secondvaluesByteCount);

            multiplyOperation<int64_t>(firstSignedINT, secondSignedINT, firstvaluesByteCount, secondvaluesByteCount, resultByteCount);

        }
        else if (std::tolower(intOrUint) == 'm')
        {
            // because of firstVal and secondVal are uint64_t
            firstHexVal = resizeHexValue<uint64_t>(firstHexVal, firstvaluesByteCount);
            secondHexVal = resizeHexValue<uint64_t>(secondHexVal, secondvaluesByteCount);

            multiplyOperation<uint64_t>(firstHexVal, secondHexVal, firstvaluesByteCount, secondvaluesByteCount, resultByteCount);
        }

        std::cout << "Do you want to reset\n";
        std::cout << "[1 / 0] \n";
        std::cin >> wantToReset;
        if (wantToReset)
        {
            system("CLS");
            continue;
        }  
        else
            break;
    }

    return 0;


}

