// ----------------------------------------------------------------------------
//  Description      : Automatic arrays
// ----------------------------------------------------------------------------
//  (c) Copyright 1999 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#ifndef IXLIB_ARRAY
#define IXLIB_ARRAY




#include <memory>




namespace ixion {
  /**
  An object that provides methods for reallocatable array management.
  
  Nothing in terms of allocation or deallocation is done automatically.
  */
  template<class T,class Allocator = std::allocator<T> >
  struct array {
    typedef T                                         value_type;
    typedef Allocator                                 allocator_type;
    typedef typename Allocator::reference             reference;
    typedef typename Allocator::const_reference       const_reference;
    typedef typename Allocator::size_type             size_type;
    typedef typename Allocator::difference_type       difference_type;
    typedef typename Allocator::pointer               pointer;
    typedef typename Allocator::const_pointer         const_pointer;
  
    protected:
    pointer               Data;
    size_type             Capacity;
    Allocator             Alloc;
  
    public:
    array(Allocator const &alloc = Allocator())
      : Data(NULL),Capacity(0),Alloc(alloc)
      { }
    array(size_type cap,Allocator const &alloc = Allocator())
      : Data(NULL),Capacity(0),Alloc(alloc)
      { allocate(cap); }
    array(array const &source)
      : Data(source.Data),Capacity(source.Capacity),Alloc(source.Alloc)
      { }
    virtual ~array()
      { }
  
    array &operator=(array const &source) {
      Data = source.Data;
      Capacity = source.Capacity;
      Alloc = source.Alloc;
      return *this;
      }
  
    reference operator[](size_type pos) const
      { return Data[pos]; }
    reference operator*() const
      { return *Data; }
    pointer operator+(size_type pos) const
      { return Data+pos; }
  
    pointer get() const // uglier method name, but more STL compliant
      { return Data; }
    size_type capacity() const
      { return Capacity; }
    allocator_type get_allocator() const
      { return Alloc; }
  
    virtual void allocate(size_type cap) {
      pointer tmp = Alloc.allocate(cap);
      if (!tmp && cap) throw std::bad_alloc();
      Data = tmp;
      Capacity = cap;
      }
    virtual void deallocate() {
      internal_deallocate();
      invalidate();
      }
    virtual void construct(pointer first,pointer last,
      const_reference value = T())
      { for (;first!=last;first++) Alloc.construct(first,value); }
    virtual void construct(pointer first,pointer last,const_pointer source)
      { for (;first!=last;first++) Alloc.construct(first,*(source++)); }
    virtual void construct(pointer item,const_reference source = T())
      { Alloc.construct(item,source); }
    virtual void destroy(pointer first,pointer last)
      { for (;first!=last;first++) Alloc.destroy(first); }
    virtual void destroy(pointer item)
      { Alloc.destroy(item); }
    virtual void invalidate() {
      Data = NULL;
      Capacity = 0;
      }
    protected:
    void internal_deallocate()
      { if (Data) Alloc.deallocate(Data,Capacity); }
  };
  
  
  
  
  /**
  An object that provides methods for reallocatable array management
  and keeps track of which (linearly consecutive) area of items has been
  constructed.
  
  Nothing in terms of allocation or deallocation is done automatically.
  */
  template<class T,class Allocator = std::allocator<T> >
  class tracking_array: public array<T,Allocator> {
    pointer FirstValid,LastValid;
    
    typedef array<T,Allocator> super;
    
    public:
    tracking_array(Allocator const &alloc = Allocator())
      : super(alloc),FirstValid(NULL),LastValid(NULL)
      { }
    tracking_array(size_type cap,Allocator const &alloc = Allocator())
      : super(cap,alloc),FirstValid(NULL),LastValid(NULL)
      { }
    tracking_array(tracking_array const &source)
      : super(source),FirstValid(source.FirstValid),LastValid(source.LastValid)
      { }
    virtual ~tracking_array()
      { }
      
    pointer begin() const
      { return FirstValid; }
    pointer end() const
      { return LastValid; }
    size_type size() const { 
      if (!FirstValid) 
        return 0;
      else
        return LastValid-FirstValid; 
      }
  
    tracking_array &operator=(tracking_array const &source) {
      FirstValid = source.FirstValid;
      LastValid = source.LastValid;
      super::operator=(source);
      return *this;
      }
    
    virtual void allocate(size_type cap) {
      FirstValid = NULL;
      LastValid = NULL;
      super::allocate(cap);
      }
    virtual void deallocate() {
      FirstValid = NULL;
      LastValid = NULL;
      super::deallocate();
      }
      
    virtual void construct(pointer first,pointer last,
      const_reference value = typename tracking_array::value_type()) { 
      if (!FirstValid || first<FirstValid) FirstValid = first;
      if (!LastValid || last>LastValid) LastValid = last;
      super::construct(first,last,value);
      }
    virtual void construct(pointer first,pointer last,const_pointer source) { 
      if (!FirstValid || first<FirstValid) FirstValid = first;
      if (!LastValid || last>LastValid) LastValid = last;
      super::construct(first,last,source);
      }
    virtual void construct(pointer item,const_reference source = T()) { 
      if (!FirstValid || item<FirstValid) FirstValid = item;
      if (!LastValid || item+1>LastValid) LastValid = item+1;
      super::construct(item,source);
      }
    virtual void destroy(pointer first,pointer last) { 
      if (first == FirstValid) FirstValid = last;
      else if (last == LastValid) LastValid = first;
      super::destroy(first,last);
      }
    virtual void destroy(pointer item) { 
      if (item+1 == LastValid) LastValid = item;
      else // this is vital if item is the last remaining item
        if (item == FirstValid) FirstValid = item+1;
      super::destroy(item);
      }
    virtual void destroy() {
      internal_destroy();
      FirstValid = NULL;
      LastValid = NULL;
      }
    virtual void invalidate() {
      super::invalidate();
      FirstValid = NULL;
      LastValid = NULL;
      }
    protected:
    void internal_destroy()
      { if (FirstValid) super::destroy(FirstValid,LastValid); }
  };
  
  
  

  /** 
  An array object that automatically deallocates the storage it allocates,
  but does nothing in terms of construction or destruction.
  */
  template<class T,class Allocator = std::allocator<T> >
  class auto_array : public array<T,Allocator> {
      typedef array<T,Allocator> super;
    
    public:
      auto_array(Allocator const &alloc = Allocator())
        : super(alloc)
        { }
      auto_array(size_type cap,Allocator const &alloc = Allocator())
        : super(cap,alloc)
        { }
      auto_array(auto_array &source)
        : super(source)
        { source.invalidate(); }
      virtual ~auto_array()
        { internal_deallocate(); }
    
      auto_array &operator=(auto_array &source) {
        internal_deallocate();
        super::operator=(source);
        source.invalidate();
        return *this;
        }
    
      virtual void allocate(size_type cap) {
        internal_deallocate();
        super::allocate(cap);
        }
  };
  
  
  
  
  /** 
  An array object that automatically deallocates the storage it allocates,
  as well as calls the appropriate constructors at the right times.
  */
  template<class T,class Allocator = std::allocator<T> >
  class auto_destroy_array: public tracking_array<T,Allocator> {
    typedef tracking_array<T,Allocator> super;
  
    public:
    auto_destroy_array(Allocator const &alloc = Allocator())
      : super(alloc)
      { }
    auto_destroy_array(size_type cap,Allocator const &alloc = Allocator())
      : super(cap,alloc)
      { }
    auto_destroy_array(auto_destroy_array &source)
      : super(source)
      { source.invalidate(); }
    virtual ~auto_destroy_array() { 
      internal_destroy();
      internal_deallocate(); 
      }
  
    auto_destroy_array &operator=(auto_destroy_array &source) {
      internal_destroy();
      internal_deallocate();
      super::operator=(source);
      source.invalidate();
      return *this;
      }
  
    virtual void allocate(size_type cap) {
      internal_destroy();
      internal_deallocate();
      super::allocate(cap);
      }
    virtual void deallocate() {
      internal_destroy();
      super::deallocate();
      }
    };
  }




#endif
