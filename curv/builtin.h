// Copyright Doug Moen 2016.
// Distributed under The MIT License.
// See accompanying file LICENSE.md or https://opensource.org/licenses/MIT

#ifndef CURV_BUILTIN_H
#define CURV_BUILTIN_H

#include <memory>
#include <curv/atom.h>
#include <curv/function.h>
#include <curv/value.h>

namespace curv {

class Meaning;
class Identifier;

struct Builtin : public aux::Shared_Base
{
    virtual Shared<Meaning> to_meaning(const Identifier&) const = 0;
};

struct Builtin_Value : public Builtin
{
    Value value_;
    Builtin_Value(Value v) : value_(std::move(v)) {}
    virtual Shared<Meaning> to_meaning(const Identifier&) const override;
};

template <class M>
struct Builtin_Meaning : public Builtin
{
    virtual Shared<Meaning> to_meaning(const Identifier& id) const override
    {
        return make<M>(share(id));
    }
};

using Namespace = Atom_Map<Shared<const Builtin>>;

const Namespace& builtin_namespace();

} // namespace curv
#endif // header guard
