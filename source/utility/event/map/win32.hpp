#ifndef CUSTOM_KEYMAP_WINDOWS
#define CUSTOM_KEYMAP_WINDOWS

#include "precompiled_header.hpp"

namespace Custom {
	namespace Event {
		KeyState MapVirtualKeyToKeyState(WPARAM wParameter) {
			switch (wParameter) {
			case '0': return KeyState::zero;
			case '1': return KeyState::one;
			case '2': return KeyState::two;
			case '3': return KeyState::three;
			case '4': return KeyState::four;
			case '5': return KeyState::five;
			case '6': return KeyState::six;
			case '7': return KeyState::seven;
			case '8': return KeyState::eight;
			case '9': return KeyState::nine;
			case 'A': return KeyState::a;
			case 'B': return KeyState::b;
			case 'C': return KeyState::c;
			case 'D': return KeyState::d;
			case 'E': return KeyState::e;
			case 'F': return KeyState::f;
			case 'G': return KeyState::g;
			case 'H': return KeyState::h;
			case 'I': return KeyState::i;
			case 'J': return KeyState::j;
			case 'K': return KeyState::k;
			case 'L': return KeyState::l;
			case 'M': return KeyState::m;
			case 'N': return KeyState::n;
			case 'O': return KeyState::o;
			case 'P': return KeyState::p;
			case 'Q': return KeyState::q;
			case 'R': return KeyState::r;
			case 'S': return KeyState::s;
			case 'T': return KeyState::t;
			case 'U': return KeyState::u;
			case 'V': return KeyState::v;
			case 'W': return KeyState::w;
			case 'X': return KeyState::x;
			case 'Y': return KeyState::y;
			case 'Z': return KeyState::z;
			case VK_TAB: return KeyState::tab;
			case VK_SPACE: return KeyState::space;
			case VK_LSHIFT: return KeyState::lshift;
			case VK_RSHIFT: return KeyState::rshift;
			case VK_LCONTROL: return KeyState::lctrl;
			case VK_RCONTROL: return KeyState::rctrl;
			case VK_LWIN: return KeyState::super;
			default: return KeyState::zero;
			}
		}
	}
}
#endif