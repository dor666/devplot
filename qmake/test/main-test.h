#pragma once

#include <QApplication>

namespace dplot {
namespace test {

/**
  * This must be shared by all instances of tests,
  * creating next one raises an sigsegv
  */
extern QApplication* app;

}
}
