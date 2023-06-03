#include "MagicalContainer.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>

namespace ariel {

// Helper function to check if a number is prime
bool isPrime(int num) {
  if (num <= 1)
    return false;

  for (int i = 2; i <= sqrt(num); ++i) {
    if (num % i == 0)
      return false;
  }

  return true;
}

void MagicalContainer::addElement(int element) {
  sortedElements.push_back(element);
  std::sort(sortedElements.begin(), sortedElements.end());
}

void MagicalContainer::removeElement(int element) {
  sortedElements.erase(
      std::remove(sortedElements.begin(), sortedElements.end(), element),
      sortedElements.end());
}

int MagicalContainer::size() const { return sortedElements.size(); }

// AscendingIterator
MagicalContainer::AscendingIterator::AscendingIterator(
    const AscendingIterator &other)
    : container(other.container), currentIndex(other.currentIndex) {}

MagicalContainer::AscendingIterator::~AscendingIterator() {}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &cont,
                                                       std::size_t index)
    : container(cont), currentIndex(index) {}

MagicalContainer::AscendingIterator &
MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other) {

  return *this;
}

bool MagicalContainer::AscendingIterator::operator==(
    const AscendingIterator &other) const {
  return false;
}

bool MagicalContainer::AscendingIterator::operator!=(
    const AscendingIterator &other) const {
  return false;
}

bool MagicalContainer::AscendingIterator::operator>(
    const AscendingIterator &other) const {
  return false;
}

bool MagicalContainer::AscendingIterator::operator<(
    const AscendingIterator &other) const {
  return false;
}

int MagicalContainer::AscendingIterator::operator*() const { return 0; }

MagicalContainer::AscendingIterator &
MagicalContainer::AscendingIterator::operator++() {

  return *this;
}

MagicalContainer::AscendingIterator
MagicalContainer::AscendingIterator::begin() const {
  return AscendingIterator(container, 0);
}

MagicalContainer::AscendingIterator
MagicalContainer::AscendingIterator::end() const {
  return AscendingIterator(container, (unsigned long)container.size());
}

// SideCrossIterator
MagicalContainer::SideCrossIterator::SideCrossIterator(
    const SideCrossIterator &other)
    : container(other.container), currentIndex(other.currentIndex),
      reverse(other.reverse) {}

MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &cont,
                                                       std::size_t index,
                                                       bool rev)
    : container(cont), currentIndex(index), reverse(rev) {}

MagicalContainer::SideCrossIterator &
MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {

  return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(
    const SideCrossIterator &other) const {
  return false;
}

bool MagicalContainer::SideCrossIterator::operator!=(
    const SideCrossIterator &other) const {
  return false;
}

bool MagicalContainer::SideCrossIterator::operator>(
    const SideCrossIterator &other) const {
  return false;
}

bool MagicalContainer::SideCrossIterator::operator<(
    const SideCrossIterator &other) const {
  return false;
}

int MagicalContainer::SideCrossIterator::operator*() const { return false; }

MagicalContainer::SideCrossIterator &
MagicalContainer::SideCrossIterator::operator++() {

  return *this;
}

MagicalContainer::SideCrossIterator
MagicalContainer::SideCrossIterator::begin() const {
  return SideCrossIterator(container, 0, reverse);
}

MagicalContainer::SideCrossIterator
MagicalContainer::SideCrossIterator::end() const {
  return SideCrossIterator(container, ((unsigned long)container.size() / 2),
                           reverse);
}

// PrimeIterator
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
    : container(other.container), currentIndex(other.currentIndex) {}

MagicalContainer::PrimeIterator::~PrimeIterator() {}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &cont,
                                               std::size_t index)
    : container(cont), currentIndex(index) {
  while (currentIndex < (unsigned long)container.size() &&
         !isPrime(container.sortedElements[currentIndex])) {
    ++currentIndex;
  }
}

MagicalContainer::PrimeIterator &
MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) {

  return *this;
}

bool MagicalContainer::PrimeIterator::operator==(
    const PrimeIterator &other) const {
  return false;
}

bool MagicalContainer::PrimeIterator::operator!=(
    const PrimeIterator &other) const {
  return false;
}

bool MagicalContainer::PrimeIterator::operator>(
    const PrimeIterator &other) const {
  return false;
}

bool MagicalContainer::PrimeIterator::operator<(
    const PrimeIterator &other) const {
  return false;
}

int MagicalContainer::PrimeIterator::operator*() const { return 0; }

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {

  return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const {
  size_t startIndex = 0;
  while (startIndex < (unsigned long)container.size() &&
         !isPrime(container.sortedElements[startIndex])) {
    ++startIndex;
  }
  return PrimeIterator(container, startIndex);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const {
  return PrimeIterator(container, (unsigned long)container.size());
}

} // namespace ariel
