#include "entity sys/components/cube_test_comp.h"

namespace wizm {

	//////////////////////////////////////////////////////////////////////////
	// DEFAULT CONSTRUCTOR
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	cube_sm_component::cube_sm_component()
	{
		draw_data = new core_arr_vertex_buffer(vertices, indices);
		draw_data->create_attrib_arr(0, 3, 5 * sizeof(float), 0);
		draw_data->create_attrib_arr(1, 2, 5 * sizeof(float), (3 * sizeof(float)));
		draw_data->create_buffer();
	}



	cube_sm_component::~cube_sm_component()
	{
	}

	//-----------------------------------------------------------------------

	void cube_sm_component::component_preupdate()
	{
	}



	void cube_sm_component::component_update()
	{
	}




	void cube_sm_component::component_postupdate()
	{
	}

	//-----------------------------------------------------------------------

}