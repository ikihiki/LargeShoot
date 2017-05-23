#pragma once

#define PROPLIKE_R(type,name) type name();
#define PROPLIKE_RNE(type,name) type name() noexcept;

#define PROPLIKE_RNE_WNE(type,name) type name() noexcept; \
							type name(type value) noexcept;

#define PROPLIKE_RC(type,name) type name() const;

#define PROPLIKE_RCNE(type,name) type name() const noexcept;

#define PROPLIKE_RC_W(type,name) type name() const; \
							type name(type value);

#define PROPLIKE_RCNE_W(type,name) type name() const noexcept; \
							type name(type value);

#define PROPLIKE_RCNE_WNE(type,name) type name() const noexcept; \
							type name(type value) noexcept;

#define PROPLIKE_RCNE_WNE_B(type,name) type __name__; \
							type name() const noexcept { return __name__;} \
							type name(type value) noexcept { __name__ = value; return value;}

#define PROPLIKE_RCECNE_WCENE(type,name) constexpr type name() const noexcept; \
							constexpr type name(type value) noexcept;
