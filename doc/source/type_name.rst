(Demangled) Type Names
=======================

*KLV* provides facilities to obtain (demangled) names of C++ types. All
following functions are in the header ``<klv/type_name.hpp>``, and they are in
the namespace ``klv``.

.. cpp:function:: bool has_demangle()

    Whether *KLV* provides demangling support.

    .. note::

        At this point, demangling is supported with GCC, Clang, and ICC.

.. cpp:function:: std::string type_name()

    ``typename<T>()`` returns a (demangled) name of type ``T``.

    .. note::

        It returns the demangled name when ``has_demangle()``, otherwise it
        returns the name as given by ``typeid(T).name()``.

.. cpp:function:: std::string type_name(x)

    Returns the (demangled) name of the type of ``x``.

.. cpp:function:: std::string demangle(const char* name)

    Demangles the input name (the one returned by ``typeid(T).name()``).

    .. note::

        When ``has_demangle()`` is true, namely, KLV has demangling support,
        this returns the demangled name, otherwise it returns a string capturing
        the intput name.
