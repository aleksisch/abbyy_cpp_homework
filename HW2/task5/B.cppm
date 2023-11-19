//
// Created by aleksey on 13.10.2023.
//
export module Example:B;

import :internals;

export namespace MyNamespace {
  class B {
    void g() {
      g_internal();
    }
  };
}
