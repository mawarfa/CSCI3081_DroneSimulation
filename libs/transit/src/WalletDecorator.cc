#include "WalletDecorator.h"

WalletDecorator::~WalletDecorator() {
}


void WalletDecorator::AddWallet(double amount) {
  this->total += amount;
}

void WalletDecorator::SubWallet(double amount) {
    this->total -= amount;
    }
