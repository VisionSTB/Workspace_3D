#include "algebra3.h"

// Simple class for hold face data
class Face{
	private:
		mat4 points;
	public:
		Face(vec4& v1, vec4& v2, vec4& v3, vec4& v4){ //deleted const's
			points[0] = v1;
			points[1] = v2;
			points[2] = v3;
			points[3] = v4;
		}
		const mat4 getPoints(){
			return points;
		}
		const vec4 getNormal(){
			vec4 r = -1*(points.getCol(1)-points.getCol(0))^(points.getCol(2)-points.getCol(1));
			return r/r.length();
		}
		void setPoints(mat4 m)
		{
			points = m;
		}
};