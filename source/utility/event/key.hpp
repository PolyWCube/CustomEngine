#ifndef CUSTOM_KEY_EVENT
#define CUSTOM_KEY_EVENT

#include "event.hpp"

namespace Custom {
	namespace Event {
		enum class KeyState : uint8_t {
			zero = 0, one = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9,
			a = 10, b = 11, c = 12, d = 13, e = 14, f = 15, g = 16, h = 17, i = 18, j = 19, k = 20, l = 21, m = 22, n = 23, o = 24, p = 25, q = 26, r =27, s = 28, t = 29, u = 30, v = 31, w = 32, x = 33, y = 34, z = 35,
			tab = 36,
			space = 37,
			lshift = 38,
			rshift = 39,
			lctrl = 40,
			rctrl = 41,
			super = 42
		};

		static std::ostream& operator<<(std::ostream& os, KeyState keyState) {
			switch (keyState) {
				case KeyState::zero: os << "0"; break;
				case KeyState::one: os << "1"; break;
				case KeyState::two: os << "2"; break;
				case KeyState::three: os << "3"; break;
				case KeyState::four: os << "4"; break;
				case KeyState::five: os << "5"; break;
				case KeyState::six: os << "6"; break;
				case KeyState::seven: os << "7"; break;
				case KeyState::eight: os << "8"; break;
				case KeyState::nine: os << "9"; break;
				case KeyState::a: os << "a"; break;
				case KeyState::b: os << "b"; break;
				case KeyState::c: os << "c"; break;
				case KeyState::d: os << "d"; break;
				case KeyState::e: os << "e"; break;
				case KeyState::f: os << "f"; break;
				case KeyState::g: os << "g"; break;
				case KeyState::h: os << "h"; break;
				case KeyState::i: os << "i"; break;
				case KeyState::j: os << "j"; break;
				case KeyState::k: os << "k"; break;
				case KeyState::l: os << "l"; break;
				case KeyState::m: os << "m"; break;
				case KeyState::n: os << "n"; break;
				case KeyState::o: os << "o"; break;
				case KeyState::p: os << "p"; break;
				case KeyState::q: os << "q"; break;
				case KeyState::r: os << "r"; break;
				case KeyState::s: os << "s"; break;
				case KeyState::t: os << "t"; break;
				case KeyState::u: os << "u"; break;
				case KeyState::v: os << "v"; break;
				case KeyState::w: os << "w"; break;
				case KeyState::x: os << "x"; break;
				case KeyState::y: os << "y"; break;
				case KeyState::z: os << "z"; break;
				case KeyState::tab: os << "tab"; break;
				case KeyState::space: os << "space"; break;
				case KeyState::lshift: os << "lshift"; break;
				case KeyState::rshift: os << "rshift"; break;
				case KeyState::lctrl: os << "lctrl"; break;
				case KeyState::rctrl: os << "rctrl"; break;
				case KeyState::super: os << "super"; break;
				default: os << "Unknown (" << static_cast<uint64_t>(keyState) << ")"; break;
			}
			return os;
		}

		class Key : public Event {
		public :
			inline KeyState getKeyState() const { return keyState; }
			DEFINE_EVENT_SOURCE(keyboard)
		protected :
			Key(KeyState keyState) : keyState(keyState) {}

			KeyState keyState;
		};

		class KeyPress : public Key {
		public :
			KeyPress(KeyState keyState, uint16_t repeat) : Key(keyState), repeat(repeat) {}

			std::string getStream() const override {
				std::ostringstream oss;
				oss << "Key Press: " << keyState << "( " << repeat << " repeats)";
				return oss.str();
			}

			inline uint16_t getRepeatCount() const { return repeat; }
			DEFINE_EVENT_ACTION(press)
		private :
			uint16_t repeat;
		};

		class KeyRelease : public Key {
		public :
			KeyRelease(KeyState keyState) : Key(keyState) {}

			std::string getStream() const override {
				std::ostringstream oss;
				oss << "Key Release: " << keyState;
				return oss.str();
			}

			DEFINE_EVENT_ACTION(release)
		};
	}
}

#endif