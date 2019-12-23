
#include "../Header/Core/SourceCommon.h"

#include "../../Include/Interface/ResourceManager.h"
#include "../Header/Impl/ResourceManagerImpl.h"

#include <memory>



VK2D_API vk2d::ResourceManager::ResourceManager(
	vk2d::_internal::RendererImpl		*	parent_renderer
)
{
	impl = std::make_unique<vk2d::_internal::ResourceManagerImpl>( parent_renderer );
	if( impl && impl->IsGood() ) {
		is_good	= true;
	} else {
		is_good	= false;
		impl	= nullptr;
		parent_renderer->Report( vk2d::ReportSeverity::CRITICAL_ERROR, "Internal error: Cannot create resource manager implementation!" );
		return;
	}
}

VK2D_API vk2d::ResourceManager::~ResourceManager()
{}

VK2D_API vk2d::TextureResource *VK2D_APIENTRY vk2d::ResourceManager::CreateTextureResource(
	vk2d::Vector2u						size,
	const std::vector<vk2d::Color8>	&	texels
)
{
	return impl->CreateTextureResource(
		size,
		texels
	);
}

VK2D_API vk2d::TextureResource * VK2D_APIENTRY vk2d::ResourceManager::LoadTextureResource(
	std::filesystem::path		file_path
)
{
	return impl->LoadTextureResource( file_path );
}

VK2D_API void VK2D_APIENTRY vk2d::ResourceManager::DestroyResource(
	vk2d::Resource		*	resource
)
{
	impl->DestroyResource( resource );
}

VK2D_API bool VK2D_APIENTRY vk2d::ResourceManager::IsGood()
{
	return is_good;
}
