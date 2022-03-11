#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

namespace GL {
class Displayable;
inline std::vector<const Displayable*> display_queue;

// a displayable object can be displayed and has a z-coordinate indicating who
// is displayed before whom ;]

class Displayable
{
protected:
    float z = 0;

public:
    Displayable(const float z_) : z { z_ } 
    {
        GL::display_queue.emplace_back(this);
    }

    virtual ~Displayable() {
        auto it = std::find(GL::display_queue.begin(), GL::display_queue.end(), this);
        GL::display_queue.erase(it);
    }

    virtual void display() const = 0;

    float get_z() const { return z; }
};

struct disp_z_cmp
{
    bool operator()(const Displayable* a, const Displayable* b) const
    {
        const auto az = a->get_z();
        const auto bz = b->get_z();
        return (az == bz) ? (a > b) : (az > bz);
    }
};


} // namespace GL
