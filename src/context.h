#pragma once

#include <bx/uint32_t.h>
#include <common.h>
#include <bgfx_utils.h>
#include <stdio.h>

#include <SDL.h>
#include <iostream>

#include "model.h"

#include <bgfx/embedded_shader.h>
#include <vs_cubes.sc.glsl.bin.h>
#include <vs_cubes.sc.essl.bin.h>
#include <vs_cubes.sc.spv.bin.h>
#include <fs_cubes.sc.glsl.bin.h>
#include <fs_cubes.sc.essl.bin.h>
#include <fs_cubes.sc.spv.bin.h>
#if defined(_WIN32)
//#include <vs_cubes.sc.dx9.bin.h>
#include <vs_cubes.sc.dx11.bin.h>
//#include <fs_cubes.sc.dx9.bin.h>
#include <fs_cubes.sc.dx11.bin.h>
#endif //  defined(_WIN32)
#if __APPLE__
#include <vs_cubes.sc.mtl.bin.h>
#include <fs.sc.mtl.bin.h>
#endif // __APPLE__


namespace
{

	struct KeyState
	{
		KeyState()
			: down(false)
		{
			for (uint32_t ii = 0; ii < entry::Key::Count; ++ii)
			{
				m_keys[ii] = entry::Key::None;
			}
		}

		bool down;
		uint8_t m_keys[entry::Key::Count];
	};


	class Context : public entry::AppI
	{
	public:

		static Context& Instance()
		{
			static Context instance;
			return instance;
		}

		/*Context(const char* _name, const char* _description, const char* _url)
			: entry::AppI(_name, _description, _url)
		{
		}*/

		Context(const char* _name = "Default App Name", const char* _description = "Default Description", const char* _url = "http://default.url")
			: entry::AppI(_name, _description, _url)
		{
		}


		void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
		{
			Args args(_argc, _argv);

			m_width = _width;
			m_height = _height;
			m_debug = BGFX_DEBUG_NONE;
			m_reset = BGFX_RESET_VSYNC;

			entry::setWindowSize(entry::kDefaultWindowHandle, m_width, m_height); // noice

			//entry::setMouseLock(entry::kDefaultWindowHandle, true);


			bgfx::Init init;
			init.type = args.m_type;
			init.vendorId = args.m_pciId;
			init.platformData.nwh = entry::getNativeWindowHandle(entry::kDefaultWindowHandle);
			init.platformData.ndt = entry::getNativeDisplayHandle();
			init.platformData.type = entry::getNativeWindowHandleType();
			//init.platformData.type = bgfx::RendererType::
			init.resolution.width = m_width;
			init.resolution.height = m_height;
			init.resolution.reset = m_reset;
			bgfx::init(init);

			bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x103040ff, 1.0f, 0);


			std::cout << entry::getNativeWindowHandleType() << "\n";

			//bgfx::RendererType::Enum type = bgfx::getRendererType();

			isRunning = true;
		}

		virtual int shutdown() override
		{
			bgfx::shutdown();
			return 0;
		}

		bool update() override
		{
			if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
			{
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

				bgfx::touch(0);






				/*
				float time = (float)((bx::getHPCounter() - m_timeOffset) / double(bx::getHPFrequency()));
				const bx::Vec3 at = { 0.0f, 0.0f,   0.0f };
				const bx::Vec3 eye = { 0.0f, 0.0f, -5.0f };
				{
					float view[16];
					bx::mtxLookAt(view, eye, at);
					float proj[16];
					bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
					bgfx::setViewTransform(0, view, proj);
					bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));
				}
				bgfx::touch(0);


				float mtx[3];
				bx::mtxRotateXY(mtx, time, time);

				bgfx::setTransform(mtx);
				*/



				isRunning = true;
				return true;
			}
			isRunning = false;
			return false;
		}

		void draw()
		{
			bgfx::frame();
		}

		entry::MouseState m_mouseState;

		entry::WindowState m_state; 

		KeyState state;

		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_debug;
		uint32_t m_reset;

		bgfx::VertexBufferHandle m_vbh;
		bgfx::IndexBufferHandle m_ibh;

		int64_t m_timeOffset;

		bool isRunning = false;

	};

} // namespace

//ENTRY_IMPLEMENT_MAIN(
//	Context
//	, "00-helloworld"
//	, "Initialization and debug text."
//	, "https://bkaradzic.github.io/bgfx/examples.html#helloworld"
//);