import { Test, TestingModule } from '@nestjs/testing';
import { UsersController } from './users.controller';
import { UsersService } from './users.service';
import { NotFoundException } from '@nestjs/common';
import { User } from './entities/user.entity';

// --- Mock Data ---
const mockUser: User = {
  id: 1,
  username: 'testuser',
  email: 'test@example.com',
} as User;

const mockUsersArray: User[] = [
  mockUser,
  { id: 2, username: 'jane', email: 'jane@example.com' } as User,
];

const mockCreateUserDto = {
  username: 'newUser',
  password: '1234',
  email: 'new@example.com',
};

const mockUpdateUserDto = {
  username: 'updatedUser',
};

// --- Mock Users Service ---
// We mock all methods used by the controller
const mockUsersService = {
  findAll: jest.fn(),
  findOne: jest.fn(),
  create: jest.fn(),
  update: jest.fn(),
  remove: jest.fn(),
};

describe('UsersController', () => {
  let controller: UsersController;

  beforeEach(async () => {
    // 1. Create the testing module, replacing the real UsersService with the mock
    const module: TestingModule = await Test.createTestingModule({
      controllers: [UsersController],
      providers: [
        {
          provide: UsersService,
          useValue: mockUsersService, // Use our mock object
        },
      ],
    }).compile();

    controller = module.get<UsersController>(UsersController);
  });

  // Reset mocks before each test
  afterEach(() => {
    jest.clearAllMocks();
  });

  it('should be defined', () => {
    expect(controller).toBeDefined();
  });

  // ====================================================================
  // 1. getAll() test
  // ====================================================================
  describe('getAll', () => {
    it('should call findAll on the service and return a list of users', async () => {
      // Arrange: Set the mock service to return the array
      mockUsersService.findAll.mockResolvedValue(mockUsersArray);

      // Act
      const result = await controller.getAll();

      // Assert
      expect(result).toEqual(mockUsersArray);
      expect(mockUsersService.findAll).toHaveBeenCalledTimes(1);
    });
  });

  // ====================================================================
  // 2. getOne() test
  // ====================================================================
  describe('getOne', () => {
    it('should call findOne on the service with the correct ID', async () => {
      // Arrange
      mockUsersService.findOne.mockResolvedValue(mockUser);
      const userId = 1;

      // Act
      const result = await controller.getOne(userId);

      // Assert
      expect(result).toEqual(mockUser);
      expect(mockUsersService.findOne).toHaveBeenCalledWith(userId);
    });

    it('should throw NotFoundException if service throws it', async () => {
      // Arrange
      mockUsersService.findOne.mockRejectedValue(new NotFoundException());

      // Act & Assert
      await expect(controller.getOne(999)).rejects.toThrow(NotFoundException);
    });
  });

  // ====================================================================
  // 3. create() test
  // ====================================================================
  describe('create', () => {
    it('should call create on the service and return the new user', async () => {
      // Arrange
      const createdUser = { ...mockUser, ...mockCreateUserDto };
      mockUsersService.create.mockResolvedValue(createdUser);

      // Act
      const result = await controller.create(mockCreateUserDto);

      // Assert
      expect(result).toEqual(createdUser);
      expect(mockUsersService.create).toHaveBeenCalledWith(mockCreateUserDto);
    });
  });

  // ====================================================================
  // 4. update() test
  // ====================================================================
  describe('update', () => {
    it('should call update on the service with the correct ID and DTO', async () => {
      // Arrange
      const updatedUser = { ...mockUser, ...mockUpdateUserDto };
      mockUsersService.update.mockResolvedValue(updatedUser);
      const userId = 1;

      // Act
      const result = await controller.update(userId, mockUpdateUserDto);

      // Assert
      expect(result).toEqual(updatedUser);
      expect(mockUsersService.update).toHaveBeenCalledWith(
        userId,
        mockUpdateUserDto,
      );
    });
  });

  // ====================================================================
  // 5. delete() test
  // ====================================================================
  describe('delete', () => {
    it('should call remove on the service with the correct ID', async () => {
      // Arrange: remove returns the deleted entity
      mockUsersService.remove.mockResolvedValue(mockUser);
      const userId = 1;

      // Act
      const result = await controller.delete(userId);

      // Assert
      expect(result).toEqual(mockUser);
      expect(mockUsersService.remove).toHaveBeenCalledWith(userId);
    });
  });
});
