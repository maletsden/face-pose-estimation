#pragma once

#include <cstddef>
#include <cstdint>

namespace Constants
{
    constexpr std::size_t FaceLandmarksNum = 68;

    namespace JawLineLandmarks
    {
        constexpr std::uint16_t Begin = 0;
        constexpr std::uint16_t End = 17;
        constexpr std::uint16_t Number = End - Begin;
    }

    namespace EyebrowLandmarks
    {
        constexpr std::uint16_t LeftBegin = 17;
        constexpr std::uint16_t LeftEnd = 22;
        constexpr std::uint16_t LeftNumber = LeftEnd - LeftBegin;

        constexpr std::uint16_t RightBegin = 22;
        constexpr std::uint16_t RightEnd = 27;
        constexpr std::uint16_t RightNumber = RightEnd - RightBegin;
    }

    namespace NoseLandmarks
    {
        constexpr std::uint16_t BridgeBegin = 27;
        constexpr std::uint16_t BridgeEnd = 31;
        constexpr std::uint16_t BridgeNumber = BridgeEnd - BridgeBegin;

        constexpr std::uint16_t LowerBegin = 31;
        constexpr std::uint16_t LowerEnd = 36;
        constexpr std::uint16_t LowerNumber = LowerEnd - LowerBegin;
    }

    namespace EyeLandmarks
    {
        constexpr std::uint16_t LeftBegin = 36;
        constexpr std::uint16_t LeftEnd = 42;
        constexpr std::uint16_t LeftNumber = LeftEnd - LeftBegin;

        constexpr std::uint16_t RightBegin = 42;
        constexpr std::uint16_t RightEnd = 48;
        constexpr std::uint16_t RightNumber = RightEnd - RightBegin;
    }

    namespace LipsLandmarks
    {
        constexpr std::uint16_t OuterBegin = 48;
        constexpr std::uint16_t OuterEnd = 60;
        constexpr std::uint16_t OuterNumber = OuterEnd - OuterBegin;

        constexpr std::uint16_t InnerBegin = 60;
        constexpr std::uint16_t InnerEnd = 67;
        constexpr std::uint16_t InnerNumber = InnerEnd - InnerBegin;
    }
}
