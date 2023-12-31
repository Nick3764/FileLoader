
#ifndef LOADER_OBSERVER_H
#define LOADER_OBSERVER_H

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};

#endif //LOADER_OBSERVER_H
