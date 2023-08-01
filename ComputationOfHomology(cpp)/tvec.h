#pragma once

template <typename T>
class TVec{
public:
	TVec() = default;
	constexpr TVec(T x, T y):x(x),y(y){}
	constexpr T getX() const {return x;};
	constexpr T getY() const {return y;};
	constexpr void setX(T x_in) { x = x_in;};
	constexpr void setY(T y_in) { y = y_in;};
public:
	constexpr bool operator==(const TVec& rhs) const{
		return (x == rhs.x && y == rhs.y);
	}
	constexpr bool operator!=(const TVec& rhs) const{
		return !(*this == rhs);
	}
	constexpr TVec operator+(const TVec& rhs) const{
		return {x + rhs.x, y + rhs.y};
	}
	constexpr TVec operator+(const T rhs) const{
		return {x + rhs, y + rhs};
	}
	constexpr TVec& operator+=(const TVec& rhs){
		 return *this = *this + rhs;
	}
	constexpr TVec operator-(const TVec& rhs) const{
		return {x - rhs.x, y - rhs.y};
	}
	constexpr TVec operator-(const T rhs) const{
		return { x - rhs, y - rhs};
	}
	constexpr TVec& operator-=(const TVec& rhs){
		return *this = *this - rhs;
	}
	constexpr TVec operator*(const TVec& rhs) const{
		return {x * rhs.x, y * rhs.y};
	}
	constexpr TVec operator*(const T rhs) const{
		return { x * rhs, y * rhs };
	}
	constexpr TVec& operator*=(const TVec& rhs){
		return *this = *this * rhs;
	}

private:
	T x;
	T y;
};