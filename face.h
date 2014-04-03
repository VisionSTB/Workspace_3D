#include "algebra3.h"

// Simple class for hold face data
class Face{
	private:
		mat4 points;
	public:
		Face(vec4& v1, vec4& v2, vec4& v3, vec4& v4){ //deleted const's
			points[0][0] = v1[0];
			points[1][0] = v1[1];
			points[2][0] = v1[2];
			points[0][1] = v2[0];
			points[1][1] = v2[1];
			points[2][1] = v2[2];
			points[0][2] = v3[0];
			points[1][2] = v3[1];
			points[2][2] = v3[2];
			points[0][3] = v4[0];
			points[1][3] = v4[1];
			points[2][3] = v4[2];
		}
		const mat4 getPoints(){
			return points;
		}
		const vec4 getNormal(){
			vec4 r = -1*(points.getCol(1)-points.getCol(0))^(points.getCol(2)-points.getCol(1));
			return r/r.length();
	}
};