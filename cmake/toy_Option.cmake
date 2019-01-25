
macro(toy_Option)

	option( TOY_ENABLE_SHARED_LIBS   "Make shared library"                  ON )
	option( TOY_ENABLE_BETA_API      "Enable unstable API"                  OFF)
	option( TOY_ENABLE_OLD_API       "Enable API that will be deprecated"   ON )
	set(    TOY_USE_GLEW                                                    ON )

endmacro(toy_Option)
