
macro(toy_Option)

	option( TOY_ENABLE_SHARED_LIBS   "Make shared library"                  ON )
	option( TOY_ENABLE_ALPHA_API     "Enable unstable API"                  OFF)
	option( TOY_ENABLE_MAY_REMOVED   "Enable API that may be deprecated"    ON )
	set(    TOY_USE_GLEW                                                    ON )

endmacro(toy_Option)
