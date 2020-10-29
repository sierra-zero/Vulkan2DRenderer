#pragma once

#include "../Core/SourceCommon.h"

#include "../Core/DescriptorSet.h"


namespace vk2d {
namespace _internal {



class WindowImpl;
class RenderTargetTextureImpl;



struct SamplerTextureDescriptorPoolData
{
	vk2d::_internal::PoolDescriptorSet						descriptor_set								= {};
	std::chrono::time_point<std::chrono::steady_clock>		previous_access_time						= {};	// For cleanup
};



struct RenderTargetTextureDependencyInfo
{
	vk2d::_internal::RenderTargetTextureImpl			*	render_target								= {};
	uint32_t												swap_buffer_index							= {};
};



/// @brief		Used to collect render information from render target texture when render is going to happen.
/// @see		vk2d::_internal::WindowImpl::EndRender().
class RenderTargetTextureRenderCollector
{
	friend WindowImpl;

public:
	struct Collection
	{
		VkSubmitInfo			vk_transfer_submit_info			= {};
		VkSubmitInfo			vk_render_submit_info			= {};
	};

	void						Append(
		VkSubmitInfo			transfer_submit_info,
		VkSubmitInfo			render_submit_info );

	vk2d::_internal::RenderTargetTextureRenderCollector::Collection				&	operator[]( size_t index );
	vk2d::_internal::RenderTargetTextureRenderCollector::Collection				*	begin();
	vk2d::_internal::RenderTargetTextureRenderCollector::Collection				*	end();
	size_t																			size();

private:
	std::vector<vk2d::_internal::RenderTargetTextureRenderCollector::Collection>	collection;
};



} // _internal
} // vk2d
