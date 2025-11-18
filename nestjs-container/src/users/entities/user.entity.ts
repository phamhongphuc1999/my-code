import { Entity, PrimaryGeneratedColumn, Column } from 'typeorm';

@Entity('Employees')
export class User {
  @PrimaryGeneratedColumn()
  id: number;

  @Column()
  username: string;

  @Column()
  email: string;
}
