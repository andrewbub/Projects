# Andrew Bub CSE30332 - Pygame: main.py
# November 20, 2017
import pygame
import math
import os
from pygame.compat import geterror
from pygame.locals import *

# Initialize the game space
class gameSpace:
	def main(self):
		pygame.init()
		self.size = self.width, self.height = 640, 420
		self.black = 0, 0, 0
		self.screen = pygame.display.set_mode(self.size)
		pygame.display.set_caption("Pygame Project")

		self.background = pygame.Surface(self.screen.get_size())
		self.background = self.background.convert()
		self.background.fill((self.black))
		self.planetDestroyed = False

# Initialize the game objects
		self.player = Player(self)
		self.enemy = Enemy(self)
		self.clock = pygame.time.Clock()

		self.sprites = pygame.sprite.Group()
		self.alderaan = pygame.sprite.RenderPlain(self.enemy)
		self.deathstar = pygame.sprite.RenderPlain(self.player)
		self.sprites.add(self.alderaan)
		self.sprites.add(self.deathstar)

		self.screen.blit(self.background, (0,0))
		pygame.display.flip()
		self.clock = pygame.time.Clock()
		self.lasers = pygame.sprite.Group()

		self.running = True
		self.victory = False

# Start the game loop
		while self.running:
# Tick regulation
			self.clock.tick(60)

# Read user input
			for event in pygame.event.get():
				if event.type == pygame.QUIT:
					self.running = False
				elif event.type == KEYDOWN:
					self.player.move(event)
				elif event.type == MOUSEMOTION:
					xMouse, yMouse = event.pos
					self.player.rotate(xMouse, yMouse)
				elif event.type == MOUSEBUTTONDOWN:
					if self.victory == True:
						self.running = False

					pos = pygame.mouse.get_pos()
					laser = Laser([pos[0] / 10.0, pos[1] / 10.0])
					self.player.fire(laser)
					self.lasers.add(laser)
					laserSprite = pygame.sprite.RenderPlain(laser)
					self.sprites.add(laserSprite)

			for laser in self.lasers:	# check for collisions, if so then end game
				rect_hit = pygame.sprite.spritecollide(laser, self.alderaan, False)

				for item in rect_hit:
					self.lasers.remove(laser)
					self.enemy.endGame()
					explosion = Explosion(self)
					explosionSprite = pygame.sprite.RenderPlain(explosion)
					self.sprites.add(explosionSprite)
					self.victory = True

				if laser.rect.y < -10:
					self.lasers.remove(laser)

# Update the screen
			self.screen.fill(self.black)
			self.sprites.update()
			self.sprites.draw(self.screen)
			pygame.display.flip()

class Explosion(pygame.sprite.Sprite):
	def __init__(self, environment):
		pygame.sprite.Sprite.__init__(self)

		self.index = 0
		self.images = []
		self.animate()
		self.image = self.images[self.index]
		self.rect = self.image.get_rect()
		self.rect.bottomright = [environment.width, environment.height]

	def animate(self):
		self.images.append(loadImageOnly("./explosion/frames000a.png"))
		self.images.append(loadImageOnly("./explosion/frames001a.png"))
		self.images.append(loadImageOnly("./explosion/frames002a.png"))
		self.images.append(loadImageOnly("./explosion/frames003a.png"))
		self.images.append(loadImageOnly("./explosion/frames004a.png"))
		self.images.append(loadImageOnly("./explosion/frames005a.png"))
		self.images.append(loadImageOnly("./explosion/frames006a.png"))
		self.images.append(loadImageOnly("./explosion/frames007a.png"))
		self.images.append(loadImageOnly("./explosion/frames008a.png"))
		self.images.append(loadImageOnly("./explosion/frames009a.png"))
		self.images.append(loadImageOnly("./explosion/frames010a.png"))
		self.images.append(loadImageOnly("./explosion/frames011a.png"))
		self.images.append(loadImageOnly("./explosion/frames012a.png"))
		self.images.append(loadImageOnly("./explosion/frames013a.png"))
		self.images.append(loadImageOnly("./explosion/frames014a.png"))
		self.images.append(loadImageOnly("./explosion/frames015a.png"))
		self.images.append(loadImageOnly("./explosion/frames016a.png"))

	def update(self):
		self.index += 1
		if self.index >= len(self.images):
			self.image.fill((0, 0, 0))
		else:
			self.image = self.images[self.index]

class Laser(pygame.sprite.Sprite):
	def __init__(self, speed):
		pygame.sprite.Sprite.__init__(self)
		self.speed = speed
		self.image, self.rect = loadImage("./laser.png")

	def update(self):
		self.rect = self.rect.move(self.speed)

class Enemy(pygame.sprite.Sprite):
	def __init__(self, environment):
		pygame.sprite.Sprite.__init__(self)
		self.image, self.rect = loadImage("./globe.png")
		self.rect.centerx = environment.width
		self.rect.centery = environment.height

	def endGame(self):
		print("\nGAME OVER\n")
		self.image.fill((0, 0, 0))

	def update(self):
		self.rect.x = self.rect.x
		self.rect.y = self.rect.y

class Player(pygame.sprite.Sprite):
	def __init__(self, environment):
		pygame.sprite.Sprite.__init__(self)
		self.defaultImage = pygame.image.load("./deathstar.png").convert_alpha()
		self.image, self.rect = loadImage("./deathstar.png")
		self.display = pygame.display.get_surface()
		self.area = self.image.get_rect()
		self.theta = 0
		self.speed = 5
		self.refresh()

	def refresh(self):
		self.position = [0, 0]

	def move(self, event):
		if event.unicode == "a":			# Shift left
			self.position[0] -= self.speed
			self.update()
		elif event.unicode == "w":			# Shift up
			self.position[1] -= self.speed
			self.update()
		if event.unicode == "d":			# Shift right
			self.position[0] += self.speed
			self.update()
		elif event.unicode == "s":			# Shift down
			self.position[1] += self.speed
			self.update()

	def rotate(self, xMouse, yMouse):
		xPlayer, yPlayer = self.rect.centery, self.rect.centerx
		self.theta = 300 - math.degrees(math.atan2(yMouse - yPlayer, xMouse - xPlayer))
		self.image = pygame.transform.rotate(self.defaultImage, self.theta)
		self.rect = self.image.get_rect(center = self.rect.center)

	def fire(self, laser):
		laser.rect.x = self.rect.centerx
		laser.rect.y = self.rect.centery

	def update(self):
		newRect = self.rect.move(self.position)
		self.rect = newRect
		pygame.event.pump()

def loadImage(name, colorkey = None):
	try:
		image = pygame.image.load(name)
	except pygame.error:
		print ("EFailed to load image: ", fullname)
		raise SystemExit(str(geterror()))

	if image.get_alpha is None:
		image = image.convert()
	else:
		image = image.convert_alpha()

	return image, image.get_rect()

def loadImageOnly(name):
	try:
		image = pygame.image.load(name)
	except pygame.error:
		print ("Failed to load images: ", fullname)
		raise SystemExit(str(geterror()))

	if image.get_alpha is None:
		image = image.convert()
	else:
		image = image.convert_alpha()

	return image
		

if __name__ == "__main__":
	gs = gameSpace()
	gs.main()
