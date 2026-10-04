#ifndef STATE_H
#define STATE_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Argument {
  public:
    virtual ~Argument() = default;
    virtual const std::vector<std::byte>& getBytes() const = 0;
};

class ValueArgument : public Argument {
  public:
    ValueArgument(std::vector<std::byte> bytes) : bytes(bytes) {}

    const std::vector<std::byte>& getBytes() const override {
        return bytes;
    }

  private:
    const std::vector<std::byte> bytes;
};

template <typename Addr> class Arguments {
  public:
    Arguments() {}

    Arguments(std::vector<std::shared_ptr<Argument>> arguments) : arguments(arguments) {}

    void addArgument(std::shared_ptr<Argument> argument) {
        arguments.push_back(argument);
    }

    std::vector<std::shared_ptr<Argument>> getArguments() const {
        return arguments;
    }

  private:
    std::vector<std::shared_ptr<Argument>> arguments;
};

template <typename Addr> class Frame {
  public:
    Frame(Addr address, Addr from, Addr to, std::string comment)
        : address(address), from(from), to(to), comment(comment) {}

    std::tuple<Addr, Addr, Addr, std::string> getContent() {
        return {address, from, to, comment};
    }

    Addr getAddress() const {
        return address;
    }

    Addr getFrom() const {
        return from;
    }

    Addr getTo() const {
        return to;
    }

    std::string getComment() const {
        return comment;
    }

  private:
    Addr address;
    Addr from;
    Addr to;
    std::string comment;
};

template <typename Addr> class StackTrace {
  public:
    StackTrace() {}

    StackTrace(std::vector<std::shared_ptr<Frame<Addr>>> frames) : frames(frames) {}
    void addFrame(std::shared_ptr<Frame<Addr>> frame) {
        frames.push_back(frame);
    }

    void reserveFrames(int numberOfFrames) {
        frames.reserve(numberOfFrames);
    }

    const std::vector<std::shared_ptr<Frame<Addr>>>& getFrames() const {
        return frames;
    }

  private:
    std::vector<std::shared_ptr<Frame<Addr>>> frames;
};

class State {
  public:
    virtual ~State() = default;
};

template <typename Addr> class TypedState : public State {
  public:
    TypedState(std::shared_ptr<Arguments<Addr>> arguments, std::shared_ptr<StackTrace<Addr>> trace)
        : arguments(arguments), trace(trace) {}

    std::shared_ptr<Arguments<Addr>> getArguments() const {
        return arguments;
    }

    std::shared_ptr<StackTrace<Addr>> getStackTrace() const {
        return trace;
    }

  private:
    std::shared_ptr<Arguments<Addr>> arguments;
    std::shared_ptr<StackTrace<Addr>> trace;
};

namespace Nodes {
class ApiCallNode;
using ApiNodePtr = std::shared_ptr<ApiCallNode>;
} // namespace Nodes

template <typename Addr> using TypedStatePtr = std::shared_ptr<TypedState<Addr>>;
template <typename Addr> using TypedStatePtrList = std::vector<TypedStatePtr<Addr>>;
template <typename Addr>
using ApiNodeToTypedStatePtrListMap =
    std::unordered_map<Nodes::ApiNodePtr, TypedStatePtrList<Addr>>;
template <typename Addr>
using TidToApiNodeToTypedStatePtrListMap =
    std::unordered_map<int, ApiNodeToTypedStatePtrListMap<Addr>>;

using StatePtr = std::shared_ptr<State>;
using StatePtrList = std::vector<StatePtr>;
using ApiNodeToStatePtrListMap = std::unordered_map<Nodes::ApiNodePtr, StatePtrList>;
using TidToApiNodeToStatePtrListMap = std::unordered_map<int, ApiNodeToStatePtrListMap>;

#endif // STATE_H