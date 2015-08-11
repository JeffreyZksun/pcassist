  * Owning pointer.  The owner uses the shared\_ptr to reference its owning objects.
  * Back pointer. The object uses the weak\_ptr to reference its owner to avoid cylic reference.
  * Pass the smart pointer object with value other than reference.
    * See http://stackoverflow.com/questions/327573/c-passing-references-to-boostshared-ptr
  * If the object is created by the new operator. It should be wrappered by the shared\_ptr.
    * Make the constructors protected and provide a static create function which returns the shared\_ptr to new the object.

```
#include "boost/weak_ptr.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"

using namespace boost;
class Object;

class ObjectImp
{
public:
    ObjectImp(weak_ptr<Object> pSelf) : m_pSelf(pSelf)
    {

    }
    ~ObjectImp()
    {

    }

    shared_ptr<Object> self()
    {
        return m_pSelf.lock();
    }

private:
    weak_ptr<Object> m_pSelf;
};

class Object : public enable_shared_from_this<Object>
{
public:
 
    ~Object()
    {

    }
    static shared_ptr<Object> create()
    {
        shared_ptr<Object> px(new Object);
        px->m_pImp = shared_ptr<ObjectImp>(new ObjectImp(weak_ptr<Object>(px)));
        return px;
    }

protected:
    Object()
    {

    }

private:
    shared_ptr<ObjectImp> m_pImp;
};


int main()
{
    shared_ptr<Object> sp = Object::create();
}

```