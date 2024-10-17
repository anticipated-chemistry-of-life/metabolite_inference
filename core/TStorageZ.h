//
// Created by VISANI Marco on 17.10.2024.
//

#ifndef TSTORAGEZ_H
#define TSTORAGEZ_H
#include <cstdint>

class TStorageZ {
private:
	uint32_t _value = 0;

	// we also add the mask
	static constexpr uint32_t _state_mask      = (1ULL << 31);
	static constexpr uint32_t _coordinate_mask = (1ULL << 31) - 1;

public:
	TStorageZ() = default;
	explicit TStorageZ(const uint32_t coordinate) {
		set_coordinate(coordinate);
		set_state(true);
	}
	[[nodiscard]] uint32_t value() const { return _value; };

	uint32_t get_coordinate() const { return _value & _coordinate_mask; };

	void set_coordinate(const uint32_t coordinate) {
		_value = (_value & ~_coordinate_mask) | (coordinate & _coordinate_mask);
	}

	bool is_one() const { return (_value & _state_mask) >> 31; }
	void set_state(const bool state) { _value = (_value & ~_state_mask) | (static_cast<uint32_t>(state)) << 31; }

	bool operator<(const TStorageZ &right) const { return get_coordinate() < right.get_coordinate(); }
	bool operator<(const uint32_t right) const { return get_coordinate() < right; }
	bool operator==(const uint32_t right) const { return get_coordinate() == right; }
	bool operator!=(const uint32_t right) const { return get_coordinate() != right; }
};

#endif // TSTORAGEZ_H
