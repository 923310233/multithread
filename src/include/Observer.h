//
// Created by 吴硕涵 on 2019-01-07.
//

#ifndef PARTONE_OBSERVER_H
#define PARTONE_OBSERVER_H

#include <boost/noncopyable.hpp>
#include <Observable.h>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

class Observer : public boost::enable_shared_from_this<Observer> {
public:
    //以多态为目的的析构必须是virtual
    virtual ~Observer();

    virtual void update() = 0;

    void observe(Observable *s) {
        s->register_(this);
    }

protected:
    Observable *subject;

};

class Foo : public Observer {
    virtual void update() {
        printf("Foo::update() %p\n", this);
    }
};

#endif //PARTONE_OBSERVER_H


