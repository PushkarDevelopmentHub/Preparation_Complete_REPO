const express = require("express");
const cookieParser = require("cookie-parser")
const authRouter = require("./routes/auth.routes")
const swaggerUi = require('swagger-ui-express');

const app = express();
app.use(express.json())
app.use(cookieParser());

// Swagger configuration
const swaggerSpec = {
  openapi: '3.0.0',
  info: {
    title: 'Bank Transaction System API',
    version: '1.0.0',
    description: 'API documentation for Bank Transaction System',
  },
  servers: [
    {
      url: 'http://localhost:3000',
      description: 'Development server',
    },
  ],
  paths: {
    '/api/auth/register': {
      post: {
        summary: 'Register a new user',
        tags: ['Auth'],
        requestBody: {
          required: true,
          content: {
            'application/json': {
              schema: {
                type: 'object',
                required: ['email', 'password', 'name'],
                properties: {
                  email: {
                    type: 'string',
                    format: 'email',
                    description: 'User\'s email address'
                  },
                  password: {
                    type: 'string',
                    minLength: 6,
                    description: 'User\'s password'
                  },
                  name: {
                    type: 'string',
                    description: 'User\'s full name'
                  }
                }
              }
            }
          }
        },
        responses: {
          201: {
            description: 'User registered successfully',
            content: {
              'application/json': {
                schema: {
                  type: 'object',
                  properties: {
                    user: {
                      type: 'object',
                      properties: {
                        _id: { type: 'string' },
                        email: { type: 'string' },
                        name: { type: 'string' }
                      }
                    },
                    token: { type: 'string' }
                  }
                }
              }
            }
          },
          422: {
            description: 'User already exists'
          }
        }
      }
    }
  }
};

// Swagger UI route
app.use('/api-docs', swaggerUi.serve, swaggerUi.setup(swaggerSpec));

app.use("/api/auth", authRouter)

module.exports = app;