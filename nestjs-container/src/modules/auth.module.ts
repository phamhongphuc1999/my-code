import { Module } from '@nestjs/common';
import { JwtModule } from '@nestjs/jwt';
import { AuthService } from 'src/services/auth.service';
import { UsersModule } from './users.module';
import { UsersController } from 'src/controllers/users.controller';

@Module({
  imports: [
    UsersModule,
    JwtModule.register({
      global: true,
      secret: 'SECRET_KEY',
      signOptions: { expiresIn: '1d' },
    }),
  ],
  providers: [AuthService],
  controllers: [UsersController],
})
export class AuthModule {}
