#ifndef Plane_H_
#define Plane_H_

#include "IComponent.h"
#include "GameObject.h"

namespace aurora
{
	class Plane : public IComponent
	{
	public:
		Plane();
		~Plane();

		void Start() override;
		
		ComponentID GetComponentId() override;

		void set_row_count(uint32_t row_count) 
		{ 
			if (row_count_ == row_count || row_count <= 0)
			{
				return;
			}

			row_count_ = row_count; 
			UpdateMesh();
		}
		uint32_t row_count() const { return row_count_; }
		
		void set_col_count(uint32_t col_count)
		{
			if (col_count_ == col_count || col_count <= 0)
			{
				return;
			}

			UpdateMesh();
		}
	protected:
		IComponentPtr Clone() override;
		void Copy(const IComponentPtr& component) override;
	private:
		void UpdateMesh();

		uint32_t row_count_;
		uint32_t col_count_;
	};
}

#endif
