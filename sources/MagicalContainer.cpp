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
  elements.push_back(element);
  sortedElements.push_back(element);
  std::sort(sortedElements.begin(), sortedElements.end());
}

void MagicalContainer::removeElement(int element) {
  elements.erase(std::remove(elements.begin(), elements.end(), element),
                 elements.end());
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
  return container.sortedElements[currentIndex] >
         container.sortedElements[other.currentIndex];
}

bool MagicalContainer::AscendingIterator::operator<(
    const AscendingIterator &other) const {
  return container.sortedElements[currentIndex] <
         container.sortedElements[other.currentIndex];
}

int MagicalContainer::AscendingIterator::operator*() const {
  return container.sortedElements[currentIndex];
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
  if (reverse) {
    return container.sortedElements[currentIndex] >
           container.sortedElements[(unsigned long)container.size() -
                                    other.currentIndex - 1];
  } else {
    return container.sortedElements[currentIndex] >
           container.sortedElements[other.currentIndex];
  }
}

bool MagicalContainer::SideCrossIterator::operator<(
    const SideCrossIterator &other) const {
  if (reverse) {
    return container.sortedElements[currentIndex] <
           container.sortedElements[(unsigned long)container.size() -
                                    other.currentIndex - 1];
  } else {
    return container.sortedElements[currentIndex] <
           container.sortedElements[other.currentIndex];
  }
}

int MagicalContainer::SideCrossIterator::operator*() const {
  if (reverse)
    return container
        .sortedElements[(unsigned long)container.size() - currentIndex - 1];
  else
    return container.sortedElements[currentIndex];
}

MagicalContainer::SideCrossIterator &
MagicalContainer::SideCrossIterator::operator++() {
  if (reverse) {
    if (currentIndex != (unsigned long)container.size() / 2)
      ++currentIndex;
    else {
      if (container.size() % 2 == 0) {
        currentIndex = (unsigned long)container.size();
      } else {
        currentIndex = (unsigned long)container.size() - 1;
        reverse = !reverse;
        return *this;
      }
    }
  }
  reverse = !reverse;
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
  return container.sortedElements[currentIndex] >
         container.sortedElements[other.currentIndex];
}

bool MagicalContainer::PrimeIterator::operator<(
    const PrimeIterator &other) const {
  return container.sortedElements[currentIndex] <
         container.sortedElements[other.currentIndex];
}

int MagicalContainer::PrimeIterator::operator*() const {
  return container.sortedElements[currentIndex];
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
  ++currentIndex;
  while (currentIndex < (unsigned long)container.size() &&
         !isPrime(container.sortedElements[currentIndex])) {
    ++currentIndex;
  }
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
