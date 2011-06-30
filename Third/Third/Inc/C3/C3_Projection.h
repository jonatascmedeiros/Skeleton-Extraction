#ifndef __C3_PROJECTION_H__
#define __C3_PROJECTION_H__

#include <C3_Math.h>
#include <C3_OpenGL.h>

namespace C3 {

using namespace Math;

//-----------------------------------------------------------------------------

inline const vec3 Project(const vec3          &obj,
                          const mat4          &pm,
						  const OGL::Viewport &vp) {

	vec4 dev(pm * vec4(obj, 1));

	return vec3(vp.x + vp.w * (dev.x + 1) * 0.5f,
	            vp.y + vp.h * (dev.y + 1) * 0.5f,
	                          (dev.z + 1) * 0.5f);
}

//-----------------------------------------------------------------------------

inline const vec3 ProjectHD(const vec3          &obj,
                            const mat4          &p,
							const mat4          &m,
							const OGL::Viewport &vp) {

	double dp[4][4];
	double dm[4][4];
	double dw[3];
	
	for (int c = 0; c < 4; ++c) {
		for (int r = 0; r < 4; ++r) {
			dp[c][r] = p[c][r];
			dm[c][r] = m[c][r];
		}
	}

	gluProject(obj.x, obj.y, obj.z, dm[0], dp[0], vp.to_ints(), &dw[0], &dw[1], &dw[2]);

	return vec3(&dw[0]);
}

//-----------------------------------------------------------------------------

inline const vec3 Unproject(const vec3          &win,
                            const mat4          &inv_pm,
							const OGL::Viewport &vp) {

	vec4 dev((2*(win.x-vp.x)/vp.w)-1,
	         (2*(win.y-vp.y)/vp.h)-1,
		      2*win.z-1,
	          1);

	return (inv_pm * dev).to_vec3();
}

//-----------------------------------------------------------------------------

inline bool Unproject(const vec3          &win,
                      const mat4          &pm,
                      const OGL::Viewport &vp,
                            vec3          *obj) {

	mat4 inv_pm(pm);

	if (invert(inv_pm)) {
		*obj = Unproject(win, inv_pm, vp);
		return true;
	} else {
		return false;
	}
}

//-----------------------------------------------------------------------------

/*
//-----------------------------------------------------------------------------

inline bool Project(const vec3          &obj,
                    const mat4          &pm,
					const OGL::Viewport &vp,
					      vec3          *win) {

	vec4 v(pm * vec4(obj, 1));

	win->x = vp.x + vp.w * (v.x + 1) * 0.5f;
	win->y = vp.y + vp.h * (v.y + 1) * 0.5f;
	win->z = (v.z + 1) * 0.5f;

	return true;
}

//-----------------------------------------------------------------------------

inline bool Project(const vec3          &obj,
                    const mat4          &m,
					const mat4          &p,
					const OGL::Viewport &vp,
					      vec3          *win) {

	return Project(obj, p*m, vp, win);
}

//-----------------------------------------------------------------------------

inline bool Unproject(const vec3          &win,
                      const mat4          &inv_pm,
                      const OGL::Viewport &vp,
                            vec3          *obj) {

	vec4 v((2*(win.x-vp.x)/vp.w)-1,
	       (2*(win.y-vp.y)/vp.h)-1,
		   2*win.z-1,
	       1);

	*obj = (inv_pm*v).to_vec3();

	return true;
}

//-----------------------------------------------------------------------------

inline bool Unproject(const vec3          &win,
                      const mat4          &m,
                      const mat4          &p,
                      const OGL::Viewport &vp,
                            vec3          *obj) {

	mat4 inv_pm(p*m);

	return (invert(inv_pm)) ? Unproject(win, inv_pm, vp, obj) : false;
}

//-----------------------------------------------------------------------------
*/
}; // namespace C3

#endif __C3_PROJECTION_H__
