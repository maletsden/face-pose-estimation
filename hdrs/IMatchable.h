#pragma once

class IMatchable
{
public:
    virtual ~IMatchable() = default;

    virtual double Cost(const IMatchable&) const = 0;
};