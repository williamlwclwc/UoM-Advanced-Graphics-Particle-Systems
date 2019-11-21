// load texture images
// according to tutorials: https://learnopengl.com/Getting-started/Textures
// referencing image loading library stb_image.h: https://github.com/nothings/stb/blob/master/stb_image.h
unsigned char *data_rock;
unsigned char *data_ground;
extern GLuint textures[2];

void loadtextures()
{
  int width, height, nrChannels;
  data_rock = stbi_load("images/lava-rock.jpg", &width, &height, &nrChannels, 0);
  if(data_rock == NULL) 
  {
    printf("failed to load texture image\n");
  } 
  else
  {
    printf("texture rock loaded\n");
  }

  int g_width, g_height, gChannels;
  data_ground = stbi_load("images/lava-ground.jpg", &g_width, &g_height, &gChannels, 0);
  if(data_ground == NULL) 
  {
    printf("failed to load texture image\n");
  } 
  else
  {
    printf("texture ground loaded\n");
  }

  glGenTextures(2, textures);

  glBindTexture(GL_TEXTURE_2D, textures[0]);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, width,
            height, 0, GL_RGB,
            GL_UNSIGNED_BYTE, data_rock);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, textures[1]);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, g_width,
            g_height, 0, GL_RGB,
            GL_UNSIGNED_BYTE, data_ground);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  if(data_rock!=NULL)
  {
    stbi_image_free(data_rock);
  }
  if(data_ground!=NULL)
  {
    stbi_image_free(data_ground);
  }
}