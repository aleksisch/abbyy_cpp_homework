export module Example:A;

import :internals;

export namespace MyNamespace {
  class A {
    void f() {
      f_internal();
    }
  };
}
