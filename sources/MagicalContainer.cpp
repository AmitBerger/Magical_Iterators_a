#include "MagicalContainer.hpp"
#include <cmath>
#include <iostream>
#include <vector>

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

void MagicalContainer::addElement(int element) { elements.push_back(element); }

void MagicalContainer::removeElement(int element) {
  for (auto it = elements.begin(); it != elements.end(); ++it) {
    if (*it == element) {
      elements.erase(it);
      break;
    }
  }
}

int MagicalContainer::size() const { return elements.size(); }

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
  if (this != &other) {
    container = other.container;
    currentIndex = other.currentIndex;
  }
  return *this;
}

bool MagicalContainer::AscendingIterator::operator==(
    const AscendingIterator &other) const {
  return currentIndex == other.currentIndex;
}

bool MagicalContainer::AscendingIterator::operator!=(
    const AscendingIterator &other) const {
  return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator>(
    const AscendingIterator &other) const {
  return currentIndex > other.currentIndex;
}

bool MagicalContainer::AscendingIterator::operator<(
    const AscendingIterator &other) const {
  return currentIndex < other.currentIndex;
}

int MagicalContainer::AscendingIterator::operator*() const {
  return container.elements[currentIndex];
}

MagicalContainer::AscendingIterator &
MagicalContainer::AscendingIterator::operator++() {
  ++currentIndex;
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
  if (this != &other) {
    container = other.container;
    currentIndex = other.currentIndex;
    reverse = other.reverse;
  }
  return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(
    const SideCrossIterator &other) const {
  return currentIndex == other.currentIndex && reverse == other.reverse;
}

bool MagicalContainer::SideCrossIterator::operator!=(
    const SideCrossIterator &other) const {
  return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator>(
    const SideCrossIterator &other) const {
  return currentIndex > other.currentIndex;
}

bool MagicalContainer::SideCrossIterator::operator<(
    const SideCrossIterator &other) const {
  return currentIndex < other.currentIndex;
}

int MagicalContainer::SideCrossIterator::operator*() const {
        if (reverse)
            return container.elements[(std::vector<int>::size_type)currentIndex];
        else
            // return container.elements[(std::vector<int>::size_type)endIndex];
            return container.elements[(std::vector<int>::size_type)((unsigned long)container.size() - currentIndex )];
    }
MagicalContainer::SideCrossIterator &
MagicalContainer::SideCrossIterator::operator++() {
  if (reverse) {
    if (currentIndex != container.size() / 2)
      ++currentIndex;
    else
      currentIndex = (unsigned long)container.size();
  }
  reverse = !reverse;
  return *this;
}

MagicalContainer::SideCrossIterator
MagicalContainer::SideCrossIterator::begin() const {
  return SideCrossIterator(container, 0, true);
}

MagicalContainer::SideCrossIterator
MagicalContainer::SideCrossIterator::end() const {
  return SideCrossIterator(container, (unsigned long)container.size(), false);
}

// PrimeIterator
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
    : container(other.container), currentIndex(other.currentIndex) {}

MagicalContainer::PrimeIterator::~PrimeIterator() {}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &cont,
                                               std::size_t index)
    : container(cont), currentIndex(index) {
  while (currentIndex < container.size() &&
         !isPrime(container.elements[currentIndex])) {
    ++currentIndex;
  }
}

MagicalContainer::PrimeIterator &
MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) {
  if (this != &other) {
    currentIndex = other.currentIndex;
  }
  return *this;
}

bool MagicalContainer::PrimeIterator::operator==(
    const PrimeIterator &other) const {
  return currentIndex == other.currentIndex;
}

bool MagicalContainer::PrimeIterator::operator!=(
    const PrimeIterator &other) const {
  return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator>(
    const PrimeIterator &other) const {
  return currentIndex > other.currentIndex;
}

bool MagicalContainer::PrimeIterator::operator<(
    const PrimeIterator &other) const {
  return currentIndex < other.currentIndex;
}

int MagicalContainer::PrimeIterator::operator*() const {
  return container.elements[currentIndex];
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
  ++currentIndex;
  while (currentIndex < container.size() &&
         !isPrime(container.elements[currentIndex])) {
    ++currentIndex;
  }
  return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const {
  return PrimeIterator(container, 0);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const {
  return PrimeIterator(container, (unsigned long)container.size());
}

} // namespace ariel
