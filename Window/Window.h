#pragma once

#include "Bases.h"

namespace Bear
{
	namespace Window
	{
		enum class KeyCode : char
		{
			Escape = 7,
			Backspace = 8,
			Tab = 9,
			Enter = 13,
			Space = 32,
			ExclamationMark = 33,
			QuotationMark = 34,
			Hash = 35,
			Dollar = 36,
			Percentage = 37,
			Ampersand = 38,
			Apostrophe = 39,
			LeftRoundBracket = 40,
			RightRoundBracket = 41,
			Asterysk = 42,
			Plus = 43,
			Comma = 44,
			Minus = 45,
			FullStop = 46,
			ForwardSlash = 47,
			Number0 = 48,
			Number1 = 49,
			Number2 = 50,
			Number3 = 51,
			Number4 = 52,
			Number5 = 53,
			Number6 = 54,
			Number7 = 55,
			Number8 = 56,
			Number9 = 57,
			Colon = 58,
			Semicolon = 59,
			LessThan = 60,
			Equal = 61,
			GreaterThan = 62,
			QuestionMark = 63,
			At = 64,
			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,
			LeftSquareBracket = 91,
			Backslash = 92,
			RightSquareBracket = 93,
			Caret = 94,
			Hyphen = 95,
			GraveAccent = 96,
			a = 97,
			b = 98,
			c = 99,
			d = 100,
			e = 101,
			f = 102,
			g = 103,
			h = 104,
			i = 105,
			j = 106,
			k = 107,
			l = 108,
			m = 109,
			n = 110,
			o = 111,
			p = 112,
			q = 113,
			r = 114,
			s = 115,
			t = 116,
			u = 117,
			v = 118,
			w = 119,
			x = 120,
			y = 121,
			z = 122,
			LeftBuckle = 123,
			VerticalLine = 124,
			RightBuckle = 125,
			Tilda = 126
		};

		enum class MouseButton : char
		{
			Left = 1,
			Right = 2,
			Middle = 16,
			XButton1 = 32,
			XButton2 = 64
		};

		enum class State : char
		{
			Restored = 1,
			Minimized = 2,
			Maximized = 3,
			FullScreen = 4
		};

		enum class PointerType
		{
			Arrow = 32512,
			Crosshair = 32515,
			Hand = 32649,
			Help = 32651,
			IBeam = 32513,
			Blocked = 32648,
			Move = 32646,
			SizeNESW = 32643,
			SizeNS = 32645,
			SizeNWSE = 32642,
			SizeWE = 32644,
			UpArrow = 32516,
			Wait = 32514
		};

		enum class Style : ULInt
		{
			Normal = 282001408,
			PopUp = 2415919104
		};

		enum class CursorState : char
		{
			Hide = 0,
			Visible = 1
		};

		struct Vector2
		{
			int x;
			int y;
		};

		class Window
		{
		private:
			void* handle;
			void* instance;
			const char* nameClass;

			const char* title;
		private:
			static LInt WinProc(void* instance, UInt msg, ULInt wParam, LInt lParam);
		private:
			Style style;
			bool destroyed;
		public:
			using Vector = Vector2;
		private:
			Vector minSize;
			Vector maxSize;
		public:
			Window(const Window& window) = delete;
			Window(const Window&& window) = delete;

			Window(const Vector& size, const Vector& position, const char* title, const PointerType& pointerType = PointerType::Arrow, const Window* parent = nullptr, const char* className = nullptr, const char* pathToTaskBarImage = nullptr, const char* pathToImage = nullptr, const State& windowState = State::Restored, const Style& windowStyle = Style::Normal);
			Window(const Vector& size, const Vector& position, const char* title, const char* pointerFileName = nullptr, const Window* parent = nullptr, const char* className = nullptr, const char* pathToTaskBarImage = nullptr, const char* pathToImage = nullptr, const State& windowState = State::Restored, const Style& windowStyle = Style::Normal);
			~Window();
		public:
			typedef void(*OnMouseMove)(const Window* window, const Vector mousePosition);
			typedef void(*OnMouseClick)(const Window* window, const MouseButton mouseButton, const Vector mousePosition, const bool controlClicked, const bool shiftClicked);
			typedef void(*OnMouseScroll)(const Window* window, const bool offset);
			typedef void(*OnCharClick)(const Window* window, const KeyCode key);
			typedef void(*OnMove)(const Window* window, const Vector position);
			typedef void(*OnResize)(const Window* window, const Vector size, const State state);
			typedef void(*OnClose)(const Window* window);
			typedef void(*OnDestroy)(const Window* window);
		public:
			OnMouseMove OnMouseMoveCallback;
			OnMouseClick OnMouseClickCallback;
			OnMouseScroll OnMouseScrollCallback;
			OnCharClick OnCharClickCallback;
			OnMove OnMoveCallback;
			OnResize OnResizeCallback;
			OnClose OnCloseCallback;
			OnDestroy OnDestroyCallback;
		public:
			void* GetHandle() const;
			void* GetInstance() const;

			const char* GetTitle() const;
			void SetTitle(const char* newTitle);

			Vector GetSize() const;
			void SetSize(const Vector& newSize);

			Vector GetPosition() const;
			void SetPosition(const Vector& newPosition);

			State GetState() const;
			void SetState(const State& newState);
		public:
			Vector GetMinSize() const;
			void SetMinSize(const Vector& size);

			Vector GetMaxSize() const;
			void SetMaxSize(const Vector& size);
		public:
			void SetCursor(const PointerType& type);
			void SetCursor(const char* pointerFileName);
		public:
			void SetMousePosition(const Vector& newPosition);
			Vector GetMousePosition() const;

			const bool IsKeyDown(const char& key) const;

			void LockMousePosition(const Vector& position, const Vector& size) const;
		public:
			void HideCursor() const;
			void ShowCursor() const;
		public:
			bool IsDestroyed() const;
		public:
			void PeekEvents() const;
			void WaitEvents() const;
		public:
			static const Vector GetMonitorResolution();
		};
	}
}