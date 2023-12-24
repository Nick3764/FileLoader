
#ifndef LOADER_OBSERVER_H
#define LOADER_OBSERVER_H

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(int value) = 0;
};

#endif //LOADER_OBSERVER_H
