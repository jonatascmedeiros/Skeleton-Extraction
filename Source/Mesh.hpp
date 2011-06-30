template <template <typename T> class C>
void Mesh::renderVertices(const C<VHandle> &vhs) const 
{
	glBegin(GL_POINTS);
	for (T::ConstIterator cv_it(vhc.begin()); cv_it != vhs.end(); ++cv_it) {
		glNormal3fv(normal3(*cv_it).to_floats());
		glVertex3fv(point3(*cv_it).to_floats());
	}
	glEnd();
}

template <template <typename T> class C>
void Mesh::renderFaces(const C<FHandle> &fhs) const 
{
	glBegin(GL_TRIANGLES);
	//glBegin(GL_LINE_LOOP);

	C<FHandle>::const_iterator cf_it(fhs.begin());
	for (; cf_it != fhs.end(); ++cf_it) {
			
		for (CFVIter cfv_it(cfv_iter(*cf_it)); cfv_it; ++cfv_it) {
			glNormal3fv(normal3(cfv_it).to_floats());
			glVertex3fv(point3(cfv_it).to_floats());
		}
	}

	glEnd();
}